#include "livegamecalculator.h"

#include <Database/drink.h>
#include <Database/livegame.h>
#include <Database/livegamedrink.h>
#include <Database/round.h>
#include <Database/point.h>
#include <Database/player.h>

#include <QDebug>

namespace Database {

LiveGameCalculator::LiveGameCalculator(LiveGame* livegame, QObject *parent) :
    QObject(parent),
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
    foreach(Point* p,Points::instance()->allRows()){
        if(m_livegame->rounds->value().contains(Rounds::instance()->rowById(p->roundId->value()))){
            hash.insert(Players::instance()->rowById(p->playerId->value()),
                        hash.value(Players::instance()->rowById(p->playerId->value())) + p->points->value());
        }
    }
    return hash;
}

} // namespace Database
