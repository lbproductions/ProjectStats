#include "gamecalculator.h"

#include <Database/game.h>
#include <Database/player.h>
#include <Database/position.h>
#include <Database/offlinegameinformation.h>
#include <Database/livegame.h>

namespace Database {

GameCalculator::GameCalculator(Game* game, QObject *parent) :
    QObject(parent),
    m_game(game)
{
}

QList<Player*> GameCalculator::calculate_players(){
    QList<Player*> list;
    if (m_game->live->value()){
	foreach(Position* p, Positions::instance()->allRows()){
	    if(p->gameId->value() == m_game->id()){
		if(!list.contains(Players::instance()->castedRowById(p->playerId->value()))){
		    //list.insert(p->position->value(),Players::instance()->castedRowById(p->playerId->value()));
                    Player* player = Players::instance()->castedRowById(p->playerId->value());
                    list.append(player);

                    static_cast<LiveGame*>(m_game)->drinksPerPlayer->addDependingAttribute(player->alcPegel);
		}
	    }
	}
    }
    else{
	foreach(OfflineGameInformation* o, OfflineGameInformations::instance()->allRows()){
	    if(o->gameId->value() == m_game->id()){
		if(!list.contains(Players::instance()->castedRowById(o->playerId->value()))){
		    //list.insert(p->position->value(),Players::instance()->castedRowById(p->playerId->value()));
		    list.append(Players::instance()->castedRowById(o->playerId->value()));
		}
	    }
	}
    }
    return list;
}

QMap<Player*,int> GameCalculator::calculate_leadingRounds(){
    QMap<Player*,int> hash;
    return hash;
}

QMap<int,QMap<Player*,int> > GameCalculator::calculate_placementAfterRounds(){
    QMap<int,QMap<Player*,int> > hash;
    return hash;
}

QMap<Player*,double> GameCalculator::calculate_averagePlacement(){
    QMap<Player*,double> hash;
    return hash;
}

QMap<Player*,int> GameCalculator::calculate_placement(){
    //qWarning() << "GameCalculator::calculate_placement() should not be executed";
    return QMap<Player*,int>();
}

QMap<Player*,int> GameCalculator::calculate_points(){
    //qWarning() << "GameCalculator::calculate_points() should not be executed";
    return QMap<Player*,int>();
}

QList<Player*> GameCalculator::calculate_playersSortedByPosition(){
    return m_game->players->value();
}

QList<Player*> GameCalculator::calculate_playersSortedByPlacement(){
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
