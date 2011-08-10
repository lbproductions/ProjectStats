#include "livegamecalculator.h"

#include <Database/drink.h>
#include <Database/livegame.h>
#include <Database/livegamedrink.h>
#include <Database/round.h>
#include <Database/point.h>
#include <Database/player.h>
#include <Database/position.h>

#include <global.h>

#include <QDebug>
#include <QTime>

namespace Database {

LiveGameCalculator::LiveGameCalculator(LiveGame* livegame, QObject *parent) :
    GameCalculator(livegame,parent),
    m_livegame(livegame)
{
}

QList<LiveGameDrink*> LiveGameCalculator::calculate_drinks(){
    QList<LiveGameDrink*> list;
    foreach(LiveGameDrink* d, LiveGameDrinks::instance()->allRows()){
        if (Rounds::instance()->rowById(d->roundId->value())->game->value()->id() == m_livegame->id()){
            list.append(d);
        }
    }
    return list;
}

QMap<Player*,QList<LiveGameDrink*> > LiveGameCalculator::calculate_drinksPerPlayer()
{
    QMap<Player*,QList<LiveGameDrink*> > hash;

    foreach(LiveGameDrink* drink, m_livegame->drinks->value())
    {
        Player* player = Players::instance()->rowById(drink->playerId->value());
        QList<LiveGameDrink*> list = hash.value(player);
        list.append(drink);
        hash.insert(player,list);
    }

    return hash;
}

QList<Round*> LiveGameCalculator::calculate_rounds(){
    QList<Round*> list;
    foreach(Round* r, Rounds::instance()->allRows()){
        if(r->gameId->value() == m_livegame->id()){
            list.append(r);
        }
    }
    return list;
}

QMap<Player*,int> LiveGameCalculator::calculate_points(){
    QMap<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        for(int j = 0; j<m_livegame->players->value().size();j++){
            hash.insert(m_livegame->players->value(j),
                        hash.value(m_livegame->players->value(j)) + m_livegame->rounds->value(i)->points->value(m_livegame->players->value(j)));
        }
    }
    return hash;
}

QTime LiveGameCalculator::calculate_length(){
    QTime time;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        time = time + m_livegame->rounds->value(i)->length->value();
    }
    return time;
}

QMap<Player*,int> LiveGameCalculator::calculate_placement(){
    QMap<Player*,int> hash;

    for (int i = 0; i<m_game->players->value().size();i++){
        Player* p = m_game->players->value(i);
        int points = m_livegame->points->value(p);
        int placement = 1;
        for (int j = 0; j<m_game->players->value().size();j++){
            if(i!=j){
                Player* pl = m_game->players->value(j);
                int pointsPl = m_livegame->points->value(pl);
                if(points < pointsPl){
                    placement++;
                }
            }
        }
        hash.insert(m_game->players->value(i),placement);
    }

    return hash;
}

int LiveGameCalculator::calculate_percComplete(){
    if(m_livegame->players->value().size() > 0){
        return (m_livegame->rounds->value().size() * 100) / (m_livegame->players->value().size() * 6);
    }
    return 0;
}

bool sortPlayersByPosition(QPair<Player*,Game*> pair1, QPair<Player*,Game*> pair2)
{
    QList<Position*> positions = Positions::instance()->allRows();
    foreach(Position* p, positions){
        foreach(Position* o, positions){
            if(o->id() != p->id()){
                if (p->gameId->value() == pair1.second->id() && o->gameId->value() == pair2.second->id()){
                    if(p->playerId->value() == pair1.first->id() && o->playerId->value() == pair2.first->id()){
                        return p->position->value() < o->position->value();
                    }
                }
            }
        }
    }
    return false;
}

QList<Player*> LiveGameCalculator::calculate_playersSortedByPosition(){
    QList<Player*> alist;
    QList<QPair<Player*,Game*> > list;
    for (int i = 0; i<m_game->players->value().size();i++){
        QPair<Player*,Game*> pair;
        pair.first = m_game->players->value(i);
        pair.second = m_game;
        list.append(pair);
    }
    qSort(list.begin(),list.end(),sortPlayersByPosition);
    for(int i = 0; i<list.size();i++){
        alist.append(list.at(i).first);
    }
    return alist;
}

bool sortPlayersByPlacement(QPair<Player*,Game*> pair1, QPair<Player*,Game*> pair2){
    return pair1.second->placement->value(pair1.first) < pair2.second->placement->value(pair2.first);
}

QList<Player*> LiveGameCalculator::calculate_playersSortedByPlacement(){
    QList<Player*> alist;
    QList<QPair<Player*,Game*> > list;
    for (int i = 0; i<m_game->players->value().size();i++){
        QPair<Player*,Game*> pair;
        pair.first = m_game->players->value(i);
        pair.second = m_game;
        list.append(pair);
    }
    qSort(list.begin(),list.end(),sortPlayersByPlacement);
    for(int i = 0; i<list.size();i++){
        alist.append(list.at(i).first);
    }
    return alist;
}

QList<Player*> LiveGameCalculator::calculate_currentPlayingPlayers(){
    /*
    if(m_livegame->currentRound->value() != 0){
        return m_livegame->currentRound->value()->currentPlayingPlayers->value();
     }
    else{
        qDebug() << "currentRound = 0 in LiveGameCalculator::calculate_currentPlayingPlayers() from Game: " + m_livegame->name->value();
        return QList<Player*>();
    }
    */
    if(m_livegame->rounds->value().isEmpty())
    {
        return QList<Player*>();
    }

    return m_livegame->rounds->value().last()->currentPlayingPlayers->value();
    //qDebug() << m_livegame->currentRound->value()->comment->value();
    //return m_livegame->currentRound->value()->currentPlayingPlayers->value();
}

Round* LiveGameCalculator::calculate_lastRound(){
    for(int i = m_livegame->rounds->value().size() - 1; i >= 0; --i)
    {
        Round *r = m_livegame->rounds->value(i);
        if(r != 0 && r->state->value() == Round::FinishedState)
        {
            return r;
        }
    }

    return 0;
}

Round* LiveGameCalculator::calculate_currentRound(){
    if(m_livegame->rounds->value().isEmpty())
    {
        return 0;
    }
    return m_livegame->rounds->value().last();
}

int LiveGameCalculator::calculate_roundCount()
{
    if(m_livegame->isFinished->value())
    {
        return m_livegame->rounds->value().size();
    }
    else
    {
        return m_livegame->rounds->value().size() - 1;
    }
}

Round::RoundState LiveGameCalculator::calculate_state(){
    if(m_livegame->currentRound->value() != 0){
        return m_livegame->currentRound->value()->state->value();
    }
    return (Round::RoundState)4;
}

Player* LiveGameCalculator::calculate_cardmixer(){
    if(m_livegame->playersSortedByPosition->value().isEmpty() ||
            m_livegame->rounds->value().isEmpty())
    {
        return 0;
    }
    Round* currentRound = m_livegame->rounds->value().last();
    int position = currentRound->cardmixerPosition->value();
    return m_livegame->playersSortedByPosition->value(position);
}

int LiveGameCalculator::calculate_totalPoints(){
    return 0;
}

bool LiveGameCalculator::calculate_isFinished()
{
    bool finished = true;
    foreach(Round *r, m_livegame->rounds->value())
    {
        finished = finished && (r != 0) && (r->state->value() == Round::FinishedState);
    }
    return finished;
}

bool sortPlayersByAlcPegel(QPair<Player*,LiveGame*> pair1, QPair<Player*,LiveGame*> pair2){
    return pair1.first->alcPegel->value(pair1.second) > pair2.first->alcPegel->value(pair2.second);
}

QList<Player*> LiveGameCalculator::calculate_playersSortedByAlcPegel(){
    QList<Player*> alist;
    if(m_livegame->drinks->value().size() > 0){
        QList<QPair<Player*,LiveGame*> > list;
        for (int i = 0; i<m_game->players->value().size();i++){
            QPair<Player*,LiveGame*> pair;
            pair.first = m_game->players->value(i);
            pair.second = m_livegame;
            list.append(pair);
        }
        qSort(list.begin(),list.end(),sortPlayersByAlcPegel);
        for(int i = 0; i<list.size();i++){
            alist.append(list.at(i).first);
        }
    }
    return alist;
}

QMap<Drink*,int> LiveGameCalculator::calculate_drinkCount(){
    QMap<Drink*,int> hash;
    foreach(LiveGameDrink* drink, m_livegame->drinks->value()){
        hash.insert(drink->drink->value(),hash.value(drink->drink->value())+1);
    }
    return hash;
}

QMap<Player*,int> LiveGameCalculator::calculate_leadingRounds(){
    QMap<Player*,int> hash;
    foreach(Player* p, m_livegame->players->value()){
        for(int i = 0; i<m_livegame->rounds->value().size();i++){
            if(m_livegame->placementAfterRounds->value(i).value(p) == 1){
                hash.insert(p,hash.value(p)+1);
            }
        }
    }
    return hash;
}

QMap<int,QMap<Player*,int> > LiveGameCalculator::calculate_placementAfterRounds(){
    QMap<int,QMap<Player*,int> > hash;
    return hash;
}

} // namespace Database
