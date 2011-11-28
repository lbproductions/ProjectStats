#include "leagueoverviewwidget.h"

#include <Gui/Misc/splitter.h>
#include <Gui/Misc/rowlist.h>
#include <Gui/Details/rowwidget.h>
#include <Gui/Details/detailswidget.h>

#include <Database/Categories/leaguefoldercategorie.h>

#include <Gui/MainWindow/mainwindow.h>

#include <Database/row.h>

#include <Models/tablemodel.h>

#include <QHBoxLayout>
#include <QScrollArea>
#include <QSettings>
#include <QHeaderView>
#include <QDebug>
#include <QFrame>

#include <Database/player.h>
#include <Gui/Filter/changematchdaybar.h>

using namespace Gui::MainWindow::Views::LeagueViewDetails;

LeagueOverviewWidget::LeagueOverviewWidget(Database::LeagueFolderCategorie *categorie, MainWindow *parent) :
    QWidget(parent),
    m_categorie(categorie)
{
    setLayout(new QHBoxLayout(this));
    layout()->setContentsMargins(0,0,0,0);

    m_basicSplitter = new Gui::Misc::Splitter(Qt::Horizontal,this);
    m_basicSplitter->setStretchFactor(0, 0);
    m_basicSplitter->setStretchFactor(1, 1);
    layout()->addWidget(m_basicSplitter);

    m_viewSplitter = new Gui::Misc::Splitter(Qt::Vertical,this);
    m_viewSplitter->setStretchFactor(0, 0);
    m_viewSplitter->setStretchFactor(1, 1);
    m_basicSplitter->addWidget(m_viewSplitter);

    m_rowListPlayer = new Gui::Misc::RowList(/*m_categorie->playersModel()*/0);
    m_rowListPlayer->setColumnHidden(1,true);
    m_rowListPlayer->setColumnHidden(8,true);
    m_rowListPlayer->setColumnHidden(9,true);

    m_rowListGames = new Gui::Misc::RowList(m_categorie->gamesModel());
    m_rowListGames->setColumnHidden(2,true);
    m_rowListGames->setColumnHidden(3,true);
    m_rowListGames->setColumnHidden(6,true);

    m_viewSplitter->addWidget(m_rowListPlayer);

    QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    ChangeMatchdayBar* bar = new ChangeMatchdayBar(this);
    layout->addWidget(m_rowListGames);
    layout->addWidget(bar);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    widget->setLayout(layout);
    m_viewSplitter->addWidget(widget);

    m_scrollAreaDetails = new QScrollArea(m_basicSplitter);
    m_scrollAreaDetails->setFrameStyle(QFrame::NoFrame);
    m_scrollAreaDetails->setAttribute(Qt::WA_MacShowFocusRect, false);
    m_scrollAreaDetails->setAutoFillBackground(true);
    m_scrollAreaDetails->setBackgroundRole(QPalette::Base);
    m_scrollAreaDetails->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollAreaDetails->setWidgetResizable(true);
    m_basicSplitter->addWidget(m_scrollAreaDetails);

    restoreSettings();

    connect(m_rowListPlayer,SIGNAL(selectionChanged()),this,SLOT(on_rowList_selectionChanged()));
    connect(m_rowListPlayer,SIGNAL(rowsSelected(QList<Database::Row*>)),this,SLOT(onPlayersListRowsSelected(QList<Database::Row*>)));
    connect(m_rowListGames,SIGNAL(selectionChanged()),this,SLOT(on_rowList_selectionChanged()));
    connect(m_rowListGames,SIGNAL(rowsSelected(QList<Database::Row*>)),this,SLOT(onGamesListRowsSelected(QList<Database::Row*>)));

    connect(bar,SIGNAL(prevClicked()),this,SIGNAL(onPrevClicked()));
    connect(bar,SIGNAL(nextClicked()),this,SIGNAL(onNextClicked()));
}

void LeagueOverviewWidget::saveSettings()
{
    QSettings settings;
    QString path = QString(m_categorie->metaObject()->className()) + "/LeagueView/";

    settings.setValue(path+"viewSplitter/Geometry",m_viewSplitter->saveGeometry());
    settings.setValue(path+"viewSplitter/WindowState",m_viewSplitter->saveState());
    settings.setValue(path+"basicSplitter/Geometry",m_basicSplitter->saveGeometry());
    settings.setValue(path+"basicSplitter/WindowState",m_basicSplitter->saveState());
    settings.setValue(path+"rowListPlayer/header/sortIndicatorSection",m_rowListPlayer->header()->sortIndicatorSection());
    settings.setValue(path+"rowListPlayer/header/sortIndicatorOrder",m_rowListPlayer->header()->sortIndicatorOrder());
    settings.setValue(path+"rowListPlayer/header/geometry",m_rowListPlayer->header()->saveGeometry());
    settings.setValue(path+"rowListPlayer/header/state",m_rowListPlayer->header()->saveState());
    settings.setValue(path+"rowListGames/header/sortIndicatorSection",m_rowListGames->header()->sortIndicatorSection());
    settings.setValue(path+"rowListGames/header/sortIndicatorOrder",m_rowListGames->header()->sortIndicatorOrder());
    settings.setValue(path+"rowListGames/header/geometry",m_rowListGames->header()->saveGeometry());
    settings.setValue(path+"rowListGames/header/state",m_rowListGames->header()->saveState());
}

void LeagueOverviewWidget::restoreSettings()
{
    QSettings settings;
    QString path = QString(m_categorie->metaObject()->className()) + "/LeagueView/";

    m_viewSplitter->restoreGeometry(settings.value(path+"viewSplitter/Geometry").toByteArray());
    m_viewSplitter->restoreState(settings.value(path+"viewSplitter/WindowState").toByteArray());
    m_basicSplitter->restoreGeometry(settings.value(path+"basicSplitter/Geometry").toByteArray());
    m_basicSplitter->restoreState(settings.value(path+"basicSplitter/WindowState").toByteArray());
    m_rowListPlayer->header()->setSortIndicator(settings.value(path+"rowListPlayer/sortIndicatorSection").toInt(),
                                            (Qt::SortOrder)settings.value(path+"rowListPlayer/sortIndicatorOrder").toInt());
    m_rowListPlayer->header()->restoreGeometry(settings.value(path+"rowListPlayer/header/geometry").toByteArray());
    m_rowListPlayer->header()->restoreState(settings.value(path+"rowListPlayer/header/state").toByteArray());

    m_rowListGames->header()->setSortIndicator(settings.value(path+"rowListGames/sortIndicatorSection").toInt(),
                                            (Qt::SortOrder)settings.value(path+"rowListGames/sortIndicatorOrder").toInt());
    m_rowListGames->header()->restoreGeometry(settings.value(path+"rowListGames/header/geometry").toByteArray());
    m_rowListGames->header()->restoreState(settings.value(path+"rowListGames/header/state").toByteArray());
}

void LeagueOverviewWidget::updateStatusbar(){

}

void LeagueOverviewWidget::onGamesListRowsSelected(QList<Database::Row *> list){
    if(list.isEmpty())
    {
        return;
    }
    Database::Row *firstRow = list.first();

    if(firstRow == 0)
    {
        return;
    }

    if(!m_rowWidget.isNull())
    {
        m_rowWidget->setVisible(false);
        m_rowWidget->deleteLater();
    }

    Details::DetailsWidget* newRowWidget = firstRow->detailsWidget();
    if(newRowWidget == 0)
    {
        return;
    }

    m_rowWidget = newRowWidget;
    m_rowWidget->setEditable(false);

    updateStatusbar();

    m_scrollAreaDetails->setWidget(m_rowWidget);
}

void LeagueOverviewWidget::onPlayersListRowsSelected(QList<Database::Row *> list){

    if(list.isEmpty())
    {
        return;
    }
    Database::Row *firstRow = list.first();

    if(firstRow == 0)
    {
        return;
    }

    if(!m_rowWidget.isNull())
    {
        m_rowWidget->setVisible(false);
        m_rowWidget->deleteLater();
    }

    Details::DetailsWidget* newRowWidget = firstRow->detailsWidget();
    if(newRowWidget == 0)
    {
        return;
    }

    m_rowWidget = newRowWidget;
    m_rowWidget->setEditable(false);

    updateStatusbar();

    m_scrollAreaDetails->setWidget(m_rowWidget);
}

void LeagueOverviewWidget::on_rowList_selectionChanged(){
    if(!m_rowWidget.isNull())
    {
        m_rowWidget->setVisible(false);
        m_rowWidget->deleteLater();
    }
}
