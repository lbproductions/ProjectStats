#include "leaguefoldercategorie.h"

#include <Gui/MainWindow/Views/LeagueView/leagueview.h>

#include "handler.h"
#include <Database/database.h>
#include <Database/game.h>
#include <Database/player.h>
#include <Database/Filters/leaguefilter.h>

#include <QIcon>

START_ROW_IMPLEMENTATION(LeagueFolderCategorie, Categorie, FolderCategorie)
{
    m_filter = new Filters::LeagueFilter();
}

QString LeagueFolderCategorie::mimeType() const
{
    return "application/projectstats.leagueFolderCategorie";
}

QIcon LeagueFolderCategorie::icon() const
{
    if(ChildCategorie::icon->value().isNull())
    {
        return QIcon(":/graphics/icons/mac/sidebar/sidebar_folder_games");
    }

    return QIcon();
}

QList<Game*> LeagueFolderCategorie::games()
{
    return m_games;
}

QList<Player*> LeagueFolderCategorie::players(){
    return m_players;
}

Gui::MainWindow::Views::View *LeagueFolderCategorie::view()
{

    if(m_view.isNull())
    {
        m_view = new Gui::MainWindow::Views::LeagueView(this);
        m_view->setWindowTitle(QString::fromUtf8("League \u2013 ")+name->value());
        m_view->setWindowIcon(icon());

        connect(m_view,SIGNAL(onPrevClicked()),this,SLOT(matchBack()));
        connect(m_view,SIGNAL(onNextClicked()),this,SLOT(matchNext()));
    }

    return m_view;
}

Models::TableModelBase* LeagueFolderCategorie::gamesModel(){
    if(m_gameModel.isNull()){
       m_gameModel = new Models::TableModel<Game,Games>(m_filter->games(),Games::instance());
    }
    return m_gameModel;
}

Models::TableModelBase* LeagueFolderCategorie::playersModel(){
    if(m_playerModel.isNull()){
       m_playerModel = new Models::TableModel<Player,Players>(m_players,Players::instance());
    }
    return m_playerModel;
}

void LeagueFolderCategorie::setPlayers(QList<Player*> players){
    m_players = players;
}

void LeagueFolderCategorie::setFilter(QPointer<Filters::LeagueFilter> filter){
    m_filter = filter;
    QList<Game*> list = m_filter->games();

    /*
    for(int i = 0; i<list.size();i++){
        m_games.append(list.at(i));
        setPlayers(m_players);
        foreach(Player* p, m_players){
            m_placementhash.insert(p->name->value()+"."+QString::number(i),placementOfPlayer(p));
        }
    }

    m_currentMatchday = m_games.size()-1;
    */
}

void LeagueFolderCategorie::matchBack(){
    /*
    if (m_games.size() > 0){        
        m_currentMatchday--;
        QPointer<Game> game = m_games.takeLast();
        m_gamesstack.push(game);
        m_gamesmodel->updateCache(game);
        m_gamesmodel->update();
        setPlayers(m_players);
        m_playersmodel->update();
    }
    */
}

void LeagueFolderCategorie::matchNext(){
    /*
    if (m_gamesstack.size() >0){        
        m_currentMatchday++;
        QPointer<Game> game = m_gamesstack.pop();
        m_games.append(game);
        m_gamesmodel->updateCache(game);
        m_gamesmodel->update();
        setPlayers(m_players);
        m_playersmodel->update();
   }
   */
}

QPixmap LeagueFolderCategorie::placeChangeOfPlayer(Player* p){
    /*
    QPixmap pixmap;
    int currentPlacement = m_placementhash.value(p->name()+"."+QString::number(m_currentMatchday));
    if (m_games.size() > 1){
        int placementBefore = m_placementhash.value(p->name()+"."+QString::number(m_currentMatchday-1));
        if (placementBefore > currentPlacement){
            pixmap.load(":/graphics/icons/general/playerstate/placeup");
            return pixmap;
        }
        else if (placementBefore < currentPlacement){
            pixmap.load(":/graphics/icons/general/playerstate/placedown");
            return pixmap;
        }
        else{
            pixmap.load(":/graphics/icons/general/playerstate/placestay");
            return pixmap;
        }
   }
   else{
        pixmap.load(":/graphics/icons/general/playerstate/placestay");
        return pixmap;
    }
    */
    return QPixmap();
}

int LeagueFolderCategorie::placementOfPlayer(Player* p){
    return 0;
}

Filters::LeagueFilter* LeagueFolderCategorie::createFilter(){
    m_filter = new Filters::LeagueFilter();
    return m_filter;
}

END_ROW_IMPLEMENTATION()
