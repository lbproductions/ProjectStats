#include "offlinegamecalculator.h"

#include <Database/offlinegame.h>
#include <Database/offlinegameinformation.h>
#include <Database/player.h>


using namespace Database;

OfflineGameCalculator::OfflineGameCalculator(OfflineGame* game):
    GameCalculator(game),
    m_offlinegame(game)
{
}

AttributeHash<Player*,int> OfflineGameCalculator::calculate_placement(){
    AttributeHash<Player*,int> hash;

    foreach(OfflineGameInformation* info, OfflineGameInformations::instance()->allRows()){
        for (int i = 0; i<m_game->players->value().size();i++){
            if(info->gameId->value() == m_offlinegame->id() && info->playerId->value() == m_game->players->value(i)->id()){
                hash.insert(m_game->players->value(i),info->placement->value());
            }
        }
    }
    return hash;
}
