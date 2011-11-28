#include "leagueview.h"

#include <Database/Categories/leaguefoldercategorie.h>

#include <Gui/MainWindow/mainwindow.h>
#include <Gui/MainWindow/Views/LeagueView/leagueoverviewwidget.h>
#include <Gui/MainWindow/Views/LeagueView/leaguegraphwidget.h>
#include <Gui/MainWindow/Views/LeagueView/leaguestatswidget.h>

#include <QHBoxLayout>

#include <QTabWidget>
#include <QDebug>


using namespace Gui::MainWindow::Views;

LeagueView::LeagueView(Database::LeagueFolderCategorie *categorie, MainWindow *parent):
    View(parent),
    m_categorie(categorie)
{
    setLayout(new QHBoxLayout(this));

    layout()->setContentsMargins(0,0,0,0);

    m_overviewwidget = new LeagueViewDetails::LeagueOverviewWidget(categorie,parent);
    m_graphwidget = new LeagueViewDetails::LeagueGraphWidget(categorie,this);
    m_statswidget = new LeagueViewDetails::LeagueStatsWidget(this);

    QTabWidget* tabwidget = new QTabWidget(this);
    tabwidget->setStyleSheet("QTabWidget::pane {" /* The tab widget frame */
                                "border: none;"
                                "background-image: url(:/graphics/styles/mac/tabbar/background);"
                                "background-repeat: repeat-x;"
                                "margin-top: -22px;"
                                "padding-top: 22px;"
                             "}"
                             "QTabBar::tab {"
                                "font-family: Lucida Grande;"
                                "font-size: 10px;"
                                "background: transparent;"
                                "height: 16px;"
                             "margin-top: 3px;"
                             "margin-bottom: 3px;"
                             "margin-right: 13px;"
                             "}"
                             "QTabBar::tab:selected {"
                                "font-weight: bold;"
                                "color: white;"
                                "border: 8px transparent;"
                                "border-left: 14px transparent;"
                                "border-right: 14px transparent;"
                                "border-image: url(:/graphics/styles/mac/tabbar/button) 8px 16px 16px 8px;"
                                "padding-top: -8px;"
                                "padding-bottom: -8px;"
                                "padding-left: -6px;"
                                "padding-right: -6px;"
                             "}");
    tabwidget->addTab(m_overviewwidget,tr("Overview"));
    tabwidget->addTab(m_graphwidget,tr("  Graphs  "));
    tabwidget->addTab(m_statswidget,tr(" Statistics "));
    layout()->addWidget(tabwidget);

}

LeagueView::~LeagueView()
{
    saveSettings();
}

void LeagueView::updateStatusbar(){

}

void LeagueView::saveSettings()
{

}

void LeagueView::restoreSettings()
{

}
