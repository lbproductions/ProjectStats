#include "leagueview.h"

#include <Database/Categories/leaguefoldercategorie.h>

#include <Gui/MainWindow/mainwindow.h>
#include <Gui/MainWindow/Sidebar/sidebar.h>
#include <Gui/MainWindow/Sidebar/sidebartreeview.h>
#include <Gui/MainWindow/Views/LeagueView/leagueoverviewwidget.h>
#include <Gui/MainWindow/Views/LeagueView/leaguegraphwidget.h>
#include <Gui/MainWindow/Views/LeagueView/leaguestatswidget.h>

#include <Database/league.h>
#include <Database/player.h>
#include <Database/game.h>

#include <Misc/handler.h>

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

    connect(Handler::getInstance()->mainWindow()->sidebar()->treeView(),SIGNAL(categorieChanged(Database::ChildCategorie*)),
            this,SLOT(on_sidebar_categorieChanged(Database::ChildCategorie*)));
    on_sidebar_categorieChanged(m_categorie);

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

void LeagueView::on_sidebar_categorieChanged(Database::ChildCategorie * c)
{
    if(c->contentType->value() == 4){
        if(c->id() == m_categorie->id()) {
            foreach(Database::Player* player, m_categorie->league()->players->value()) {
                QList<Database::Game*> games;
                foreach(Database::Game* game, m_categorie->league()->games->value()) {
                    if(game->players->value().contains(player)) {
                        games.append(game);
                    }
                }
                player->games->changeValue(games);
                if(m_categorie->league()->gameType->value() == "Doppelkopf") {
                    player->dokoStats()->dokoGames->changeValue(games);
                }
            }
        }
     }
    else{
        foreach(Database::Player* p, Database::Players::instance()->allRows()) {
            p->games->recalculateFromScratch();
            if(m_categorie->league()->gameType->value() == "Doppelkopf") {
                p->dokoStats()->dokoGames->recalculateFromScratch();
            }
        }
    }
}

void LeagueView::saveSettings()
{
}

void LeagueView::restoreSettings()
{

}
