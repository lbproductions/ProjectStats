#include "placecalculator.h"

#include "../place.h"
#include "../game.h"
#include "../playerplaceassignment.h"
#include "../player.h"

namespace Database {


PlaceCalculator::PlaceCalculator(Place* place, QObject *parent) :
    QObject(parent),
    m_place(place)
{
}

int PlaceCalculator::calculate_gameCount(){
    int count = 0;
    foreach(Game* g, Games::instance()->allRows()){
        if (g->siteId->value() == m_place->id()){
            count++;
        }
    }
    return count;
}

QList<Player*> PlaceCalculator::calculate_players(){
    QList<Player*> list;
    foreach(PlayerPlaceAssignment* a, PlayerPlaceAssignments::instance()->allRows()){
        if(a->placeId->value() == m_place->id()){
            list.append(Players::instance()->castedRowById(a->playerId->value()));
        }
    }
    return list;
}

} // namespace Database
