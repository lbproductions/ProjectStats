#include "playercalculator.h"

#include <Database/game.h>
#include <Database/player.h>
#include <Database/place.h>

#include <Database/attributelist.h>

#include <QDebug>
#include <QDateTime>

namespace Database {

PlayerCalculator::PlayerCalculator(QPointer<Player> player,QObject *parent):
    QObject(parent),
    m_player(player)
{
}

AttributeList<Game*> PlayerCalculator::calculate_games(){
    AttributeList<Game*> list;
    foreach(Game* g, Games::instance()->allRows()){
	if(g->players->value().contains(m_player)){
	    list.append(g);
	}
    }

    return list;
}

AttributeList<Place*> PlayerCalculator::calculate_places(){
    AttributeList<Place*> list;
    foreach(Place* p, Places::instance()->allRows()){
	if(p->player->value() == m_player){
	    list.append(p);
	}
    }
    return list;
}

int PlayerCalculator::calculate_points(){
    int points = 0;
    AttributeList<Game*> list = m_player->games->value();
    for(int i = 0; i<list.size();i++){
        Game* g = list.at(i);
        double zaehler = (double)(g->players->value().size() - g->placement->value(m_player));
        double nenner = (double)g->players->value().size()-1;
	points = points + 100* (zaehler / nenner);
    }
    return points;
}

double PlayerCalculator::calculate_average(){
    if(m_player->games->value().size() > 0){
        return (double)m_player->points->value() / (double)m_player->games->value().size();
    }
    else{
    return 0.0;
    }
}

int PlayerCalculator::calculate_wins(){
    int count = 0;
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->placement->value(m_player) == 1){
            count++;
        }
    }
    return count;
}

int PlayerCalculator::calculate_losses(){
    int count = 0;
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->placement->value(m_player) == m_player->games->value(i)->players->value().size()){
            count++;
        }
    }
    return count;
}

QDateTime PlayerCalculator::calculate_lastGame(){
    QDateTime time(QDate(1960,1,1));
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->date->value() > time){
            time = m_player->games->value(i)->date->value();
        }
    }
    return time;
}

QDateTime PlayerCalculator::calculate_lastWin(){
    QDateTime time(QDate(1960,1,1));
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->date->value() > time && m_player->games->value(i)->placement->value(m_player) == 1){
            time = m_player->games->value(i)->date->value();
        }
    }
    return time;
}

} // namespace Database
