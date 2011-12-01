#include "listview.h"

#include <Database/Categories/childcategorie.h>
#include <Gui/Misc/rowlist.h>
#include <Gui/Misc/splitter.h>
#include <Gui/Details/rowwidget.h>
#include <Gui/Details/rowwindow.h>
#include <Gui/Details/detailswidget.h>
#include <Gui/Details/summarywidget.h>
#include <Gui/MainWindow/mainwindow.h>
#include <Gui/MainWindow/statusbar.h>
#include <Misc/handler.h>
#include <Gui/Misc/sheet.h>

#include <QHBoxLayout>
#include <QScrollArea>
#include <QSettings>
#include <QHeaderView>
#include <QAction>
#include <QDebug>

using namespace Gui::MainWindow::Views;

ListView::ListView(Database::ChildCategorie *categorie, MainWindow *parent) :
    View(parent),
    m_categorie(categorie),
    m_rowWidget(0),
    m_editButtonAction(0)
{
    setLayout(new QHBoxLayout(this));
    layout()->setContentsMargins(0,0,0,0);

    m_horizontalSplitter = new Misc::Splitter(Qt::Vertical,this);
    m_horizontalSplitter->setStretchFactor(0, 0);
    m_horizontalSplitter->setStretchFactor(1, 1);
    layout()->addWidget(m_horizontalSplitter);

    m_rowList = new Misc::RowList(categorie->model(),this);
    m_rowList->setDragEnabled(true);
    connect(m_rowList,SIGNAL(selectionChanged()),this,SLOT(on_rowList_selectionChanged()));
    connect(m_rowList,SIGNAL(rowsSelected(QList<Database::Row*>)),this,SLOT(on_rowList_rowsSelected(QList<Database::Row*>)));
    connect(m_rowList,SIGNAL(rowDoubleClicked(Database::Row*)),this,SLOT(on_rowList_rowDoubleClicked(Database::Row*)));

    m_horizontalSplitter->addWidget(m_rowList);

    m_scrollAreaDetails = new QScrollArea(m_horizontalSplitter);
    m_scrollAreaDetails->setFrameStyle(QFrame::NoFrame);
    m_scrollAreaDetails->setAttribute(Qt::WA_MacShowFocusRect, false);
    m_scrollAreaDetails->setAutoFillBackground(true);
    m_scrollAreaDetails->setBackgroundRole(QPalette::Base);
    m_scrollAreaDetails->setStyleSheet("QScrollArea {"
                                       "background: transparent;"
                                       "border-top: 43px transparent;"
                                       "border-image: url(:/graphics/images/greybackground2) 43px 0px 0px 0px repeat;"
                                       "margin: 0px;"
                                       "padding-top: -43px;"
                     "}");
    m_scrollAreaDetails->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollAreaDetails->setWidgetResizable(true);

    m_sheet = new Gui::Misc::Sheet(m_scrollAreaDetails);
    m_sheet->setVisible(false);

    m_horizontalSplitter->addWidget(m_scrollAreaDetails);

    restoreSettings();
}

ListView::~ListView()
{
    saveSettings();
}

void ListView::saveSettings()
{
    QSettings settings;
    QString path = QString(m_categorie->metaObject()->className()) + "/ListView/";

    settings.setValue(path+"horizontalSplitter/Geometry",m_horizontalSplitter->saveGeometry());
    settings.setValue(path+"horizontalSplitter/WindowState",m_horizontalSplitter->saveState());
    settings.setValue(path+"rowList/header/sortIndicatorSection",m_rowList->header()->sortIndicatorSection());
    settings.setValue(path+"rowList/header/sortIndicatorOrder",m_rowList->header()->sortIndicatorOrder());
    settings.setValue(path+"rowList/header/geometry",m_rowList->header()->saveGeometry());
    settings.setValue(path+"rowList/header/state",m_rowList->header()->saveState());
}

void ListView::restoreSettings()
{
    QSettings settings;
    QString path = QString(m_categorie->metaObject()->className()) + "/ListView/";

    m_horizontalSplitter->restoreGeometry(settings.value(path+"horizontalSplitter/Geometry").toByteArray());
    m_horizontalSplitter->restoreState(settings.value(path+"horizontalSplitter/WindowState").toByteArray());
    m_rowList->header()->setSortIndicator(settings.value(path+"rowList/sortIndicatorSection").toInt(),
					    (Qt::SortOrder)settings.value(path+"rowList/sortIndicatorOrder").toInt());
    m_rowList->header()->restoreGeometry(settings.value(path+"rowList/header/geometry").toByteArray());
    m_rowList->header()->restoreState(settings.value(path+"rowList/header/state").toByteArray());
}

void ListView::on_rowList_selectionChanged()
{   
    if(m_rowWidget)
    {
        m_rowWidget->setVisible(false);
        m_rowWidget->deleteLater();
    }
}

void ListView::on_rowList_rowsSelected(QList<Database::Row *> list)
{
    if(list.isEmpty())
    {


        return;
    }
    Database::Row *firstRow = list.first();

    if(firstRow == 0)
    {
        return;
    }

    if(m_rowWidget)
    {
        m_sheet->setVisible(false);
        m_rowWidget->setVisible(false);
        m_rowWidget->deleteLater();
        m_rowWidget = 0;
    }

    Details::SummaryWidget* summaryWidget = static_cast<Gui::Details::SummaryWidget*>(firstRow->summaryWidget());

    if(summaryWidget == 0){
        Details::RowWidget* newRowWidget = static_cast<Gui::Details::RowWidget*>(firstRow->rowWidget());
        if(newRowWidget == 0 || firstRow->detailsWidget() == 0)
        {
            return;
        }

        m_rowWidget = newRowWidget;
        m_rowWidget->detailsWidget()->setEditable(false);

        if(m_rowWidget && m_rowWidget->detailsWidget() != 0 && m_editButtonAction)
        {
             m_rowWidget->detailsWidget()->setEditable(m_editButtonAction->isChecked());
        }

        updateStatusbar();

        m_sheet->setWidget(m_rowWidget);
        m_sheet->setVisible(true);
        m_scrollAreaDetails->setWidget(m_sheet);
    }
    else{
        m_sheet->setWidget(summaryWidget);
        m_sheet->setVisible(true);
        m_scrollAreaDetails->setWidget(m_sheet);
    }


}

void ListView::on_rowList_rowDoubleClicked(Database::Row *row)
{
    if(row == 0)
    {
        return;
    }

    Details::RowWindow *newRowWindow = static_cast<Gui::Details::RowWindow*>(row->rowWindow());
    if(newRowWindow)
    {
        newRowWindow->show();
        return;
    }

    Details::RowWidget* newRowWidget = static_cast<Gui::Details::RowWidget*>(row->rowWidget());
    if(newRowWidget)
    {
        newRowWidget->show();
    }
}

void Gui::MainWindow::Views::ListView::updateStatusbar()
{
    if(Handler::getInstance()->mainWindow() &&
        Handler::getInstance()->mainWindow()->statusBar())
    {
        if(m_rowWidget &&
            m_rowWidget->detailsWidget() != 0 &&
            m_rowWidget->detailsWidget()->mayBeEditable())
        {
            Handler::getInstance()->mainWindow()->statusBar()->setLeftButton(tr("Edit"),editButtonAction());
        }
        else
        {
            Handler::getInstance()->mainWindow()->statusBar()->disableLeftButton();
        }
    }
}

QAction * Gui::MainWindow::Views::ListView::editButtonAction()
{
    if(!m_editButtonAction)
    {
        m_editButtonAction = new QAction(this);
        m_editButtonAction->setCheckable(true);
        connect(m_editButtonAction,SIGNAL(toggled(bool)),this,SLOT(on_editActionToggled(bool)));
    }

    return m_editButtonAction;
}

void Gui::MainWindow::Views::ListView::on_editActionToggled(bool checked)
{
    if(m_rowWidget && m_rowWidget->detailsWidget() != 0)
    {
        m_rowWidget->detailsWidget()->setEditable(checked);
    }
}
