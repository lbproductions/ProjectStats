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

QList<Drink*> LiveGameCalculator::calculate_drinks(){
    qDebug() << "calculate_drinks wird ausgeführt";
    QList<Drink*> list;
    foreach(LiveGameDrink* d, LiveGameDrinks::instance()->allRows()){
        if (Rounds::instance()->rowById(d->roundId->value())->game->value()->id() == m_livegame->id()){
            list.append(Drinks::instance()->rowById(d->drinkId->value()));
        }
    }
    qDebug() << "Drink-Size in " + m_livegame->name->value() + " ist " + QString::number(list.size());
    return list;
}

QList<Round*> LiveGameCalculator::calculate_rounds(){
    qDebug() << "calculate_rounds wird ausgeführt";
    QList<Round*> list;
    foreach(Round* r, Rounds::instance()->allRows()){
        if(r->gameId->value() == m_livegame->id()){
            list.append(r);
        }
    }
    return list;
}

} // namespace Database
