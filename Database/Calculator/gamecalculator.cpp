#include "gamecalculator.h"

#include <Database/game.h>
#include <Database/player.h>
#include <Database/position.h>
#include <Database/offlinegameinformation.h>

namespace Database {

GameCalculator::GameCalculator(Game* game, QObject *parent) :
    QObject(parent),
    m_game(game)
{
}

AttributeList<Player*> GameCalculator::calculate_players(){
    AttributeList<Player*> list;
    if (m_game->live->value()){
	foreach(Position* p, Positions::instance()->allRows()){
	    if(p->gameId->value() == m_game->id()){
		if(!list.contains(Players::instance()->rowById(p->playerId->value()))){
		    //list.insert(p->position->value(),Players::instance()->rowById(p->playerId->value()));
		    list.append(Players::instance()->rowById(p->playerId->value()));
		}
	    }
	}
    }
    else{
	foreach(OfflineGameInformation* o, OfflineGameInformations::instance()->allRows()){
	    if(o->gameId->value() == m_game->id()){
		if(!list.contains(Players::instance()->rowById(o->playerId->value()))){
		    //list.insert(p->position->value(),Players::instance()->rowById(p->playerId->value()));
		    list.append(Players::instance()->rowById(o->playerId->value()));
		}
	    }
	}
    }
    return list;
}

AttributeHash<Player*,int> GameCalculator::calculate_placement(){
    //qWarning() << "GameCalculator::calculate_placement() should not be executed";
    return AttributeHash<Player*,int>();
}

AttributeHash<Player*,int> GameCalculator::calculate_points(){
    //qWarning() << "GameCalculator::calculate_points() should not be executed";
    return AttributeHash<Player*,int>();
}

AttributeList<Player*> GameCalculator::calculate_playersSortedByPosition(){
    return m_game->players->value();
}

AttributeList<Player*> GameCalculator::calculate_playersSortedByPlacement(){
    return m_game->players->value();
}

QTime GameCalculator::calculate_length(){
    return QTime();
}

int GameCalculator::calculate_totalPoints(){
    return 0;
}

Round::RoundState GameCalculator::calculate_state(){
    return (Round::RoundState)4;
}

} // namespace Database
