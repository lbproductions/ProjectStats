#include "playercalculator.h"

#include <Database/game.h>
#include <Database/player.h>
#include <Database/place.h>

#include <Database/attributelist.h>

#include <QDebug>

namespace Database {

PlayerCalculator::PlayerCalculator(QPointer<Player> player,QObject *parent):
    QObject(parent),
    m_player(player)
{
}

QList<Game*> PlayerCalculator::calculate_games(){
    QList<Game*> list;
    foreach(Game* g, Games::instance()->allRows()){
        if(g->players->value()->contains(m_player)){
            list.append(g);
        }
    }

    return list;
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

int PlayerCalculator::calculate_points(){
    int points = 0;
    foreach(Game* g, m_player->games->value()){
        double zaehler = (double)(g->players->value()->size() - g->placement->value(m_player));
        double nenner = (double)g->players->value()->size()-1;
        points = points + 100* (zaehler / nenner);
    }
    return points;
}

} // namespace Database
