#include "livegamecalculator.h"

#include <Database/drink.h>
#include <Database/livegame.h>
#include <Database/livegamedrink.h>
#include <Database/round.h>

namespace Database {

LiveGameCalculator::LiveGameCalculator(LiveGame* livegame, QObject *parent) :
    QObject(parent),
    m_livegame(livegame)
{
}

QList<Drink*> LiveGameCalculator::calculate_drinks(){
    QList<Drink*> list;
    foreach(LiveGameDrink* d, LiveGameDrinks::instance()->allRows()){
        if (Rounds::instance()->rowById(d->roundId->value())->game->value()->id() == m_livegame->id()){
            list.append(Drinks::instance()->rowById(d->drinkId->value()));
        }
    }
    return list;
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

} // namespace Database
