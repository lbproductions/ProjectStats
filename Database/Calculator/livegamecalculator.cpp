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

AttributeList<LiveGameDrink*> LiveGameCalculator::calculate_drinks(){
    AttributeList<LiveGameDrink*> list;
    foreach(LiveGameDrink* d, LiveGameDrinks::instance()->allRows()){
	if (Rounds::instance()->rowById(d->roundId->value())->game->value()->id() == m_livegame->id()){
            list.append(d);
	}
    }
    return list;
}

AttributeHash<Player*,AttributeList<LiveGameDrink*> > LiveGameCalculator::calculate_drinksPerPlayer()
{
    AttributeHash<Player*,AttributeList<LiveGameDrink*> > hash;

    foreach(LiveGameDrink* drink, m_livegame->drinks->value())
    {
        Player* player = Players::instance()->rowById(drink->playerId->value());
        AttributeList<LiveGameDrink*> list = hash.value(player);
        list.append(drink);
        hash.insert(player,list);
    }

    return hash;
}

AttributeList<Round*> LiveGameCalculator::calculate_rounds(){
    AttributeList<Round*> list;
    foreach(Round* r, Rounds::instance()->allRows()){
	if(r->gameId->value() == m_livegame->id()){
	    list.append(r);
	}
    }
    return list;
}

AttributeHash<Player*,int> LiveGameCalculator::calculate_points(){
    AttributeHash<Player*,int> hash;
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

AttributeHash<Player*,int> LiveGameCalculator::calculate_placement(){
    AttributeHash<Player*,int> hash;

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

bool sortPlayersByPosition(QPair<Player*,Game*> pair1, QPair<Player*,Game*> pair2){
    foreach(Position* p, Positions::instance()->allRows()){
        foreach(Position* o, Positions::instance()->allRows()){
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

AttributeList<Player*> LiveGameCalculator::calculate_playersSortedByPosition(){
    AttributeList<Player*> alist;
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

AttributeList<Player*> LiveGameCalculator::calculate_playersSortedByPlacement(){
    AttributeList<Player*> alist;
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

AttributeList<Player*> LiveGameCalculator::calculate_currentPlayingPlayers(){
    /*
    if(m_livegame->currentRound->value() != 0){
        return m_livegame->currentRound->value()->currentPlayingPlayers->value();
     }
    else{
        qDebug() << "currentRound = 0 in LiveGameCalculator::calculate_currentPlayingPlayers() from Game: " + m_livegame->name->value();
        return AttributeList<Player*>();
    }
    */
    if(m_livegame->rounds->value().isEmpty())
    {
        return AttributeList<Player*>();
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

} // namespace Database
