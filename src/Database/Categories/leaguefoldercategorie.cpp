#include "leaguefoldercategorie.h"

#include "smartfoldercategorie.h"
#include "playersfoldercategorie.h"
#include "gamesfoldercategorie.h"

#include <Database/Filters/enoughleagueplayersrule.h>
#include <Gui/MainWindow/Views/LeagueView/leagueview.h>
#include <Database/categorie.h>

#include <Misc/handler.h>
#include <Database/database.h>
#include <Database/game.h>
#include <Database/player.h>

#include <QIcon>

using namespace Database;

LeagueFolderCategorie::LeagueFolderCategorie() :
    FolderCategorie(0,Categories::instance())
{
    initializeAttributes();

    type->setValue(Categorie::FolderCategorieType);
    contentType->setValue(ChildCategorie::LeagueCategorieContentType);
    parentId->setValue(6);

    m_table->insertRow(this);

    SmartFolderCategorie* gamesFolder = new SmartFolderCategorie();
    gamesFolder->parentId->setValue(m_id);
    gamesFolder->contentType->setValue(ChildCategorie::GamesCategorieContentType);
    addChildRow(gamesFolder);
    gamesFolder->setFilter(new EnoughLeaguePlayersRule());

    PlayersFolderCategorie* playersFolder = new PlayersFolderCategorie();
    playersFolder->parentId->setValue(m_id);
    addChildRow(playersFolder);
}

LeagueFolderCategorie::LeagueFolderCategorie(const LeagueFolderCategorie &other) :
    FolderCategorie(other.m_id, other.m_table)
{
    initializeAttributes();
}
LeagueFolderCategorie::LeagueFolderCategorie(int id, TableBase *table) : FolderCategorie(id,table)
{
    initializeAttributes();
}

void LeagueFolderCategorie::initializeAttributes()
{
    IMPLEMENT_ATTRIBUTE(PlayersFolderCategorie*, LeagueFolderCategorie, playersFolder, tr("Players Folder"))
    IMPLEMENT_ATTRIBUTE(SmartFolderCategorie*, LeagueFolderCategorie, gamesFolder, tr("Games Folder"))

    m_gamesModel = 0;
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

SmartFolderCategorie* LeagueFolderCategorie::calculate_gamesFolder()
{
    QList<Categorie*> qlist = Categories::instance()->rowsBySqlCondition("WHERE parentId = "+QString::number(m_id)+" AND contentType = "+QString::number(ChildCategorie::GamesCategorieContentType));
    if(!qlist.isEmpty())
    {
        return static_cast<SmartFolderCategorie*>(qlist.at(0));
    }

    return 0;
}

PlayersFolderCategorie* LeagueFolderCategorie::calculate_playersFolder()
{
    QList<Categorie*> qlist = Categories::instance()->rowsBySqlCondition("WHERE parentId = "+QString::number(m_id)+" AND contentType = "+QString::number(ChildCategorie::PlayersCategorieContentType));
    if(!qlist.isEmpty())
    {
        return static_cast<PlayersFolderCategorie*>(qlist.at(0));
    }

    return 0;
}

void LeagueFolderCategorie::addPlayer(Player* player)
{
    playersFolder->value()->addPlayer(player);

    static_cast<EnoughLeaguePlayersRule*>(gamesFolder->value()->filter->value())->addPlayer(player);
}

Models::TableModelBase* LeagueFolderCategorie::gamesModel()
{
    if(!m_gamesModel)
    {
        SmartFolderCategorie* folder = static_cast<SmartFolderCategorie*>(gamesFolder->value());
        QList<Game*> games = folder->getAll<Game,Games>();
        m_gamesModel = new Models::TableModel<Game,Games>(games,Games::instance());
    }
    return m_gamesModel;
}

//Models::TableModelBase* LeagueFolderCategorie::playersModel(){
//    if(m_playerModel.isNull()){
//       m_playerModel = new Models::TableModel<Player,Players>(m_players,Players::instance());
//    }
//    return m_playerModel;
//}

//void LeagueFolderCategorie::setPlayers(QList<Player*> players){
//    m_players = players;

//    foreach(Player* player, players)
//    {
//        insertRow(player);
//    }
//}

//void LeagueFolderCategorie::setFilter(){
//    //QList<Game*> list = m_filter->games();

//    /*
//    for(int i = 0; i<list.size();i++){
//        m_games.append(list.at(i));
//        setPlayers(m_players);
//        foreach(Player* p, m_players){
//            m_placementhash.insert(p->name->value()+"."+QString::number(i),placementOfPlayer(p));
//        }
//    }

//    m_currentMatchday = m_games.size()-1;
//    */
//}

//void LeagueFolderCategorie::matchBack(){
//    /*
//    if (m_games.size() > 0){
//        m_currentMatchday--;
//        QPointer<Game> game = m_games.takeLast();
//        m_gamesstack.push(game);
//        m_gamesmodel->updateCache(game);
//        m_gamesmodel->update();
//        setPlayers(m_players);
//        m_playersmodel->update();
//    }
//    */
//}

//void LeagueFolderCategorie::matchNext(){
//    /*
//    if (m_gamesstack.size() >0){
//        m_currentMatchday++;
//        QPointer<Game> game = m_gamesstack.pop();
//        m_games.append(game);
//        m_gamesmodel->updateCache(game);
//        m_gamesmodel->update();
//        setPlayers(m_players);
//        m_playersmodel->update();
//   }
//   */
//}

//QPixmap LeagueFolderCategorie::placeChangeOfPlayer(Player* p){
//    /*
//    QPixmap pixmap;
//    int currentPlacement = m_placementhash.value(p->name()+"."+QString::number(m_currentMatchday));
//    if (m_games.size() > 1){
//        int placementBefore = m_placementhash.value(p->name()+"."+QString::number(m_currentMatchday-1));
//        if (placementBefore > currentPlacement){
//            pixmap.load(":/graphics/icons/general/playerstate/placeup");
//            return pixmap;
//        }
//        else if (placementBefore < currentPlacement){
//            pixmap.load(":/graphics/icons/general/playerstate/placedown");
//            return pixmap;
//        }
//        else{
//            pixmap.load(":/graphics/icons/general/playerstate/placestay");
//            return pixmap;
//        }
//   }
//   else{
//        pixmap.load(":/graphics/icons/general/playerstate/placestay");
//        return pixmap;
//    }
//    */
//    return QPixmap();
//}

//int LeagueFolderCategorie::placementOfPlayer(Player* p){
//    return 0;
//}

////Filters::LeagueFilter* LeagueFolderCategorie::createFilter(){
////    //m_filter = new Filters::LeagueFilter();
////    return m_filter;
////}
