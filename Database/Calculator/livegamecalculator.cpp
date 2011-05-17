#include "livegamecalculator.h"

#include <Database/drink.h>
#include <Database/livegame.h>
#include <Database/livegamedrink.h>
#include <Database/round.h>

#include <QDebug>

namespace Database {

LiveGameCalculator::LiveGameCalculator(LiveGame* livegame, QObject *parent) :
    QObject(parent),
    m_livegame(livegame)
{
}

AttributeList<Drink*>* LiveGameCalculator::calculate_drinks(){
    AttributeList<Drink*>* list = new AttributeList<Drink*>(this);
    foreach(LiveGameDrink* d, LiveGameDrinks::instance()->allRows()){
        if (Rounds::instance()->rowById(d->roundId->value())->game->value()->id() == m_livegame->id()){
            list->append(Drinks::instance()->rowById(d->drinkId->value()));
        }
    }
    return list;
}

AttributeList<Round*>* LiveGameCalculator::calculate_rounds(){
    AttributeList<Round*>* list = new AttributeList<Round*>(this);
    foreach(Round* r, Rounds::instance()->allRows()){
        if(r->gameId->value() == m_livegame->id()){
            list->append(r);
        }
    }
    return list;
}

} // namespace Database
