#include "playercalculator.h"

#include <Database/game.h>
#include <Database/player.h>
#include <Database/place.h>

#include <QDebug>

namespace Database {

PlayerCalculator::PlayerCalculator(QPointer<Player> player,QObject *parent):
    QObject(parent),
    m_player(player)
{

}

int PlayerCalculator::calculate_games(){
    int count = 0;
    foreach(Game* g, Games::instance()->allRows()){
        if(g->players->value().contains(m_player)){
            count++;
        }
    }

    return count;
}

QList<Place*> PlayerCalculator::calculate_places(){
    QList<Place*> list;
    foreach(Place* p, Places::instance()->allRows()){
        if(p->player->value() == m_player){
            list.append(p);
        }
    }
    return list;
}

} // namespace Database
