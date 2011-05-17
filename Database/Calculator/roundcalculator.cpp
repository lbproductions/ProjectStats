#include "roundcalculator.h"

#include <Database/player.h>
#include <Database/round.h>
#include <Database/point.h>

#include <QObject>

using namespace Database;

RoundCalculator::RoundCalculator(Round* round):
    QObject(round),
    m_round(round)
{
}

AttributeHash<Player*,int> RoundCalculator::calculate_points(){
    AttributeHash<Player*,int> hash;
    foreach(Point* p,Points::instance()->allRows()){
        if(p->roundId->value() == m_round->id()){
            hash.insert(Players::instance()->rowById(p->playerId->value()),
                        p->points->value());
        }
    }
    return hash;
}
