#include "drinkcalculator.h"

#include "../livegamedrink.h"
#include "../drink.h"
#include "../livegame.h"
#include "../player.h"

#include <QDebug>

namespace Database {

DrinkCalculator::DrinkCalculator(Drink* drink, QObject *parent) :
    QObject(parent),
    m_drink(drink)
{
}

QMap<Player*,int> DrinkCalculator::calculate_countPerPlayer(){
    QMap<Player*,int> hash;
    foreach(LiveGameDrink* d, LiveGameDrinks::instance()->allRows()){
        if(d->drinkId->value() == m_drink->id()){
            Player* p = Players::instance()->rowById(d->playerId->value());
            hash.insert(p,hash.value(p)+1);
        }
    }
    return hash;
}

int DrinkCalculator::calculate_drinkCount(){
    int count = 0;
    foreach(Player* p, m_drink->countPerPlayer->value().keys()){
        count += m_drink->countPerPlayer->value(p);
    }
    return count;
}

QString DrinkCalculator::calculate_mostDrinks(){
    Player* player = 0;
    foreach(Player* p, m_drink->countPerPlayer->value().keys()){
        if(m_drink->countPerPlayer->value(p) > m_drink->countPerPlayer->value(player)){
            player = p;
        }
    }
    if(player != 0){
        return player->name->value() + " (" + QString::number(100*m_drink->countPerPlayer->value(player)/m_drink->drinkCount->value()) + "%)";
    }
    else{
        return "";
    }
}

} // namespace Database
