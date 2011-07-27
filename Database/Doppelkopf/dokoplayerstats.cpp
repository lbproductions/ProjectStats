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
    liveGames = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("liveGames",tr("LiveGames"), this);
    liveGames->setCalculationFunction(this,&DokoPlayerStats::calculate_liveGames);
    dokoGames->addDependingAttribute(liveGames);
    offlineGames = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("offlineGames",tr("OfflineGames"), this);
    offlineGames->setCalculationFunction(this,&DokoPlayerStats::calculate_offlineGames);
    dokoGames->addDependingAttribute(offlineGames);
    points = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("points",tr("Points"), this);
    points->setCalculationFunction(this,&DokoPlayerStats::calculate_points);
    livePoints = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("livePoints",tr("LivePoints"), this);
    livePoints->setCalculationFunction(this,&DokoPlayerStats::calculate_livePoints);
    liveGames->addDependingAttribute(livePoints);
    livePoints->addDependingAttribute(points);
    offlinePoints = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("offlinePoints",tr("OfflinePoints"), this);
    offlinePoints->setCalculationFunction(this,&DokoPlayerStats::calculate_offlinePoints);
    offlineGames->addDependingAttribute(offlinePoints);
    offlinePoints->addDependingAttribute(points);


    hochzeiten = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("hochzeiten",tr("Hochzeiten"), this);
    hochzeiten->setCalculationFunction(this,&DokoPlayerStats::calculate_hochzeiten);
    dokoGames->addDependingAttribute(hochzeiten);
    soli = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("soli",tr("Soli"), this);
    soli->setCalculationFunction(this,&DokoPlayerStats::calculate_soli);
    dokoGames->addDependingAttribute(soli);
    trumpfabgaben = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("trumpfabgaben",tr("Trumpfabgaben"), this);
    trumpfabgaben->setCalculationFunction(this,&DokoPlayerStats::calculate_trumpfabgaben);
    dokoGames->addDependingAttribute(trumpfabgaben);
    schweinereien = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("schweinereien",tr("Schweinereien"), this);
    schweinereien->setCalculationFunction(this,&DokoPlayerStats::calculate_schweinereien);
    dokoGames->addDependingAttribute(schweinereien);
    schmeissereien = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("schmeissereien",tr("Schmeissereien"), this);
    schmeissereien->setCalculationFunction(this,&DokoPlayerStats::calculate_schmeissereien);
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

AttributeList<Game*> DokoPlayerStats::calculate_dokoGames(){
    AttributeList<Game*>  list;
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

int DokoPlayerStats::calculate_liveGames(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            count++;
        }
    }
    return count;
}

int DokoPlayerStats::calculate_offlineGames(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(!g->live->value()){
            count++;
        }
    }
    return count;
}

int DokoPlayerStats::calculate_livePoints(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            count += g->points->value(m_player);
        }
    }
    return count;
}

int DokoPlayerStats::calculate_offlinePoints(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(!g->live->value()){
            count += g->points->value(m_player);
        }
    }
    return count;
}

int DokoPlayerStats::calculate_points(){
    return offlinePoints->value() + livePoints->value();
}


