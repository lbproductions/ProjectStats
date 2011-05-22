#include "livegamecalculator.h"

#include <Database/drink.h>
#include <Database/livegame.h>
#include <Database/livegamedrink.h>
#include <Database/round.h>
#include <Database/point.h>
#include <Database/player.h>

#include <global.h>

#include <QDebug>
#include <QTime>

namespace Database {

LiveGameCalculator::LiveGameCalculator(LiveGame* livegame, QObject *parent) :
    GameCalculator(livegame,parent),
    m_livegame(livegame)
{
}

AttributeList<Drink*> LiveGameCalculator::calculate_drinks(){
    AttributeList<Drink*> list;
    foreach(LiveGameDrink* d, LiveGameDrinks::instance()->allRows()){
	if (Rounds::instance()->rowById(d->roundId->value())->game->value()->id() == m_livegame->id()){
	    list.append(Drinks::instance()->rowById(d->drinkId->value()));
	}
    }
    return list;
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

} // namespace Database
