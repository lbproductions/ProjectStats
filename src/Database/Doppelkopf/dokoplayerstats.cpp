#include "dokoplayerstats.h"

#include <Database/player.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoofflinegame.h>

using namespace Database;

DokoPlayerStats::DokoPlayerStats(Player* player):
    m_player(player)
{
    dokoGames = new ListAttribute<Game*,DokoPlayerStats, DokoPlayerStats>("dokoGames",tr("DokoGames"), this);
    dokoGames->setCalculationFunction(this,&DokoPlayerStats::calculate_dokoGames);

    hochzeiten = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("hochzeiten",tr("Hochzeiten"), this);
    hochzeiten->setCalculationFunction(this,&DokoPlayerStats::calculate_hochzeiten);
    m_player->registerAttribute(hochzeiten);
    dokoGames->addDependingAttribute(hochzeiten);

    soli = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("soli",tr("Soli"), this);
    soli->setCalculationFunction(this,&DokoPlayerStats::calculate_soli);
    m_player->registerAttribute(soli);
    dokoGames->addDependingAttribute(soli);

    trumpfabgaben = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("trumpfabgaben",tr("Trumpfabgaben"), this);
    trumpfabgaben->setCalculationFunction(this,&DokoPlayerStats::calculate_trumpfabgaben);
    m_player->registerAttribute(trumpfabgaben);
    dokoGames->addDependingAttribute(trumpfabgaben);

    schweinereien = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("schweinereien",tr("Schweinereien"), this);
    schweinereien->setCalculationFunction(this,&DokoPlayerStats::calculate_schweinereien);
    m_player->registerAttribute(schweinereien);
    dokoGames->addDependingAttribute(schweinereien);

    schmeissereien = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("schmeissereien",tr("Schmeissereien"), this);
    schmeissereien->setCalculationFunction(this,&DokoPlayerStats::calculate_schmeissereien);
    m_player->registerAttribute(schmeissereien);
    dokoGames->addDependingAttribute(schmeissereien);
}

QList<AttributeBase*> DokoPlayerStats::attributes() const
{
    return QList<AttributeBase*>();
}


AttributeBase *DokoPlayerStats::attribute(const QString &/*name*/) const
{
    return 0;
}

QList<Game*> DokoPlayerStats::calculate_dokoGames(){
    QList<Game*>  list;
    foreach(Game* g, m_player->games->value()){
        if(g->type->value() == "Doppelkopf"){
          list.append(g);
        }
    }
    return list;
}

int DokoPlayerStats::calculate_hochzeiten(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            QPointer<DokoLiveGame> game = static_cast<DokoLiveGame*>(g);
            count += game->doko_hochzeit->value(m_player);
        }
        else{
            QPointer<DokoOfflineGame> game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

int DokoPlayerStats::calculate_soli(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            QPointer<DokoLiveGame> game = static_cast<DokoLiveGame*>(g);
            count += game->doko_solo->value(m_player);
        }
        else{
            QPointer<DokoOfflineGame> game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

int DokoPlayerStats::calculate_trumpfabgaben(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            QPointer<DokoLiveGame> game = static_cast<DokoLiveGame*>(g);
            count += game->doko_trumpfabgabe->value(m_player);
        }
        else{
            QPointer<DokoOfflineGame> game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

int DokoPlayerStats::calculate_schmeissereien(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            QPointer<DokoLiveGame> game = static_cast<DokoLiveGame*>(g);
            count += game->doko_schmeisserei->value(m_player);
        }
        else{
            QPointer<DokoOfflineGame> game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

int DokoPlayerStats::calculate_schweinereien(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            QPointer<DokoLiveGame> game = static_cast<DokoLiveGame*>(g);
            count += game->doko_schweinerei->value(m_player);
        }
        else{
            QPointer<DokoOfflineGame> game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

