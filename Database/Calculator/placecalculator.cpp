#include "placecalculator.h"

#include <Database/place.h>
#include <Database/game.h>

namespace Database {


PlaceCalculator::PlaceCalculator(Place* place, QObject *parent) :
    QObject(parent),
    m_place(place)
{
}

int PlaceCalculator::calculate_gameCount(){
    int count = 0;
    foreach(Game* g, Games::instance()->allRows()){
        if (g->site->value() == m_place){
            count++;
        }
    }
    return count;
}

} // namespace Database
