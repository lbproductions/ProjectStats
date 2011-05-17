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

AttributeList<Player*>* GameCalculator::calculate_players(){
    AttributeList<Player*>* list = new AttributeList<Player*>(this);
    if (m_game->live->value()){
        foreach(Position* p, Positions::instance()->allRows()){
            if(p->gameId->value() == m_game->id()){
                if(!list->contains(Players::instance()->rowById(p->playerId->value()))){
                    //list.insert(p->position->value(),Players::instance()->rowById(p->playerId->value()));
                    list->append(Players::instance()->rowById(p->playerId->value()));
                }
            }
        }
    }
    else{
        foreach(OfflineGameInformation* o, OfflineGameInformations::instance()->allRows()){
            if(o->gameId->value() == m_game->id()){
                if(!list->contains(Players::instance()->rowById(o->playerId->value()))){
                    //list.insert(p->position->value(),Players::instance()->rowById(p->playerId->value()));
                    list->append(Players::instance()->rowById(o->playerId->value()));
                }
            }
        }
    }
    return list;
}

AttributeHash<Player*,int>* GameCalculator::calculate_placement(){
    qDebug() << "calculate_placement wird ausgeführt";
    AttributeHash<Player*,int>* hash = new AttributeHash<Player*,int>();
    for (int i = 0; i<m_game->players->value()->size();i++){
        hash->insert(m_game->players->value(i),i+1);
    }
    connect(hash,SIGNAL(changed()),m_game->placement,SIGNAL(changed()));
    foreach(Player* p, hash->keys()){
        qDebug() << p->name->value() << ":" << hash->value(p);
    }
    return hash;
}

} // namespace Database