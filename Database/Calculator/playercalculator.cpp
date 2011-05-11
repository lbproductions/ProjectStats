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

AttributeList<Game*>* PlayerCalculator::calculate_games(){
    AttributeList<Game*>* list = new AttributeList<Game*>(this);
    foreach(Game* g, Games::instance()->allRows()){
        if(g->players->value()->contains(m_player)){
            list->append(g);
        }
    }

    return list;
}

AttributeList<Place*>* PlayerCalculator::calculate_places(){
    AttributeList<Place*>* list = new AttributeList<Place*>(this);
    foreach(Place* p, Places::instance()->allRows()){
        if(p->player->value() == m_player){
            list->append(p);
        }
    }
    return list;
}

int PlayerCalculator::calculate_points(){
    /*
    int points = 0;
    for(int i = 0; i<m_player->games->value()->size();i++){
        Game* g = m_player->games->value(i);
        double zaehler = (double)(g->players->value()->size() - g->placement->value(m_player));
        double nenner = (double)g->players->value()->size()-1;
        points = points + 100* (zaehler / nenner);
    }
    return points;
    */
}

} // namespace Database
