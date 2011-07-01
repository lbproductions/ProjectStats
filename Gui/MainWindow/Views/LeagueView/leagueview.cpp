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
    //tabwidget->setStyleSheet(" QTabBar::tab {background: rgb(51,51,51); min-width: 200px; color: white; padding: 2px; border: 1px solid white;}");
    tabwidget->addTab(m_overviewwidget,"Overview");
    tabwidget->addTab(m_graphwidget,"Graphs");
    tabwidget->addTab(m_statswidget,"Stats");
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
