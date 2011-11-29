#include "dokoplayerstats.h"

#include <Database/player.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoofflinegame.h>

#include <Misc/global.h>

using namespace Database;

DokoPlayerStats::DokoPlayerStats(Player* player):
    m_player(player)
{
    dokoGames = new ListAttribute<Game*,DokoPlayerStats, DokoPlayerStats>("dokoGames",tr("DokoGames"), this);
    dokoGames->setCalculationFunction(this,&DokoPlayerStats::calculate_dokoGames);

    re = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("re",tr("Re"), this);
    re->setCalculationFunction(this,&DokoPlayerStats::calculate_re);
    m_player->registerAttribute(re);
    dokoGames->addDependingAttribute(re);

    rePercentage = new Attribute<double,DokoPlayerStats, DokoPlayerStats>("rePercentage",tr("RePercentage"), this);
    rePercentage->setCalculationFunction(this,&DokoPlayerStats::calculate_rePercentage);
    m_player->registerAttribute(rePercentage);
    dokoGames->addDependingAttribute(rePercentage);

    reWins = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("reWins",tr("ReWins"), this);
    reWins->setCalculationFunction(this,&DokoPlayerStats::calculate_reWins);
    m_player->registerAttribute(reWins);
    dokoGames->addDependingAttribute(reWins);

    reWinsPercentage = new Attribute<double,DokoPlayerStats, DokoPlayerStats>("reWinsPercentage",tr("ReWinsPercentage"), this);
    reWinsPercentage->setCalculationFunction(this,&DokoPlayerStats::calculate_reWinsPercentage);
    m_player->registerAttribute(reWinsPercentage);
    dokoGames->addDependingAttribute(reWinsPercentage);

    contra = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("contra",tr("Contra"), this);
    contra->setCalculationFunction(this,&DokoPlayerStats::calculate_contra);
    m_player->registerAttribute(contra);
    dokoGames->addDependingAttribute(contra);

    contraPercentage = new Attribute<double,DokoPlayerStats, DokoPlayerStats>("contraPercentage",tr("ContraPercentage"), this);
    contraPercentage->setCalculationFunction(this,&DokoPlayerStats::calculate_contraPercentage);
    m_player->registerAttribute(contraPercentage);
    dokoGames->addDependingAttribute(contraPercentage);

    contraWins = new Attribute<int,DokoPlayerStats, DokoPlayerStats>("contraWins",tr("ContraWins"), this);
    contraWins->setCalculationFunction(this,&DokoPlayerStats::calculate_contraWins);
    m_player->registerAttribute(contraWins);
    dokoGames->addDependingAttribute(contraWins);

    contraWinsPercentage = new Attribute<double,DokoPlayerStats, DokoPlayerStats>("contraWinsPercentage",tr("ContraWinsPercentage"), this);
    contraWinsPercentage->setCalculationFunction(this,&DokoPlayerStats::calculate_contraWinsPercentage);
    m_player->registerAttribute(contraWinsPercentage);
    dokoGames->addDependingAttribute(contraWinsPercentage);

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

    pointAveragePerRound = new Attribute<double,DokoPlayerStats, DokoPlayerStats>("pointAveragePerRound",tr("PointAveragePerRound"), this);
    pointAveragePerRound->setCalculationFunction(this,&DokoPlayerStats::calculate_pointAveragePerRound);
    m_player->registerAttribute(pointAveragePerRound);
    dokoGames->addDependingAttribute(pointAveragePerRound);

    roundWinsPercentage = new Attribute<double,DokoPlayerStats, DokoPlayerStats>("roundWinsPercentage",tr("RoundWinsPercentage"), this);
    roundWinsPercentage->setCalculationFunction(this,&DokoPlayerStats::calculate_roundWinsPercentage);
    m_player->registerAttribute(roundWinsPercentage);
    dokoGames->addDependingAttribute(roundWinsPercentage);
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
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_hochzeit->value(m_player);
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

int DokoPlayerStats::calculate_soli(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_solo->value(m_player);
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

int DokoPlayerStats::calculate_trumpfabgaben(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_trumpfabgabe->value(m_player);
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

int DokoPlayerStats::calculate_schmeissereien(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_schmeisserei->value(m_player);
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

int DokoPlayerStats::calculate_schweinereien(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_schweinerei->value(m_player);
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

int DokoPlayerStats::calculate_re(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_re->value(m_player);
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

double DokoPlayerStats::calculate_rePercentage(){
    int count = 0;
    int count1 = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_rePercentage->value(m_player);
            count1++;
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    if(count1 > 0){
        return round((double)count / (double)count1,2);
    }
    else{
        return 0;
    }
}

int DokoPlayerStats::calculate_reWins(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_reWins->value(m_player);
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

double DokoPlayerStats::calculate_reWinsPercentage(){
    int count = 0;
    int count1 = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_reWinsPercentage->value(m_player);
            count1++;
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    if(count1 > 0){
        return round((double)count / (double)count1,2);
    }
    else{
        return 0;
    }
}

int DokoPlayerStats::calculate_contra(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_contra->value(m_player);
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

double DokoPlayerStats::calculate_contraPercentage(){
    int count = 0;
    int count1 = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_contraPercentage->value(m_player);
            count1++;
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    if(count1 > 0){
        return round((double)count / (double)count1,2);
    }
    else{
        return 0;
    }
}

int DokoPlayerStats::calculate_contraWins(){
    int count = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_contraWins->value(m_player);
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    return count;
}

double DokoPlayerStats::calculate_contraWinsPercentage(){
    int count = 0;
    int count1 = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_contraWinsPercentage->value(m_player);
            count1++;
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    if(count1 > 0){
        return round((double)count / (double)count1,2);
    }
    else{
        return 0;
    }
}

double DokoPlayerStats::calculate_pointAveragePerRound(){
    double count = 0.0;
    int count1 = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_pointAveragePerWin->value(m_player);
            count1++;
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    if(count1 > 0){
        return count / (double)count1;
    }
    else{
        return 0.0;
    }
}

double DokoPlayerStats::calculate_roundWinsPercentage(){
    double count = 0.0;
    int count1 = 0;
    foreach(Game* g, this->dokoGames->value()){
        if(g->live->value()){
            DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
            count += game->doko_roundWinsPercentage->value(m_player);
            count1++;
        }
        else{
            DokoOfflineGame* game = static_cast<DokoOfflineGame*>(g);
        }
    }
    if(count1 > 0){
        return count / (double)count1;
    }
    else{
        return 0.0;
    }
}

