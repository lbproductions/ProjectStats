#include "drinkcalculator.h"

#include <Database/livegamedrink.h>
#include <Database/drink.h>
#include <Database/livegame.h>

#include <QDebug>

namespace Database {

DrinkCalculator::DrinkCalculator(Drink* drink, QObject *parent) :
    QObject(parent),
    m_drink(drink)
{
}

int DrinkCalculator::calculate_drinkCount(){
    int count = 0;
    foreach(Game* g, Games::instance()->allRows()){
        if(g->live->value()){
            LiveGame* l = static_cast<LiveGame*>(g);
            foreach(LiveGameDrink* d, l->drinks->value()){
                if(d->drinkId->value() == m_drink->id()){
                    count++;
                }
            }
        }
    }
    return count;
}

} // namespace Database
