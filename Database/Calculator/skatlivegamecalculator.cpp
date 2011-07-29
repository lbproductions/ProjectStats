#include "skatlivegamecalculator.h"

#include <Database/Skat/skatlivegame.h>

namespace Database {

SkatLiveGameCalculator::SkatLiveGameCalculator(SkatLiveGame* game):
    LiveGameCalculator(game),
    m_skatlivegame(game)
{
}

QMap<Player*,int> SkatLiveGameCalculator::calculate_placement(){
    QMap<Player*,int> hash;

    for (int i = 0; i<m_game->players->value().size();i++){
        Player* p = m_game->players->value(i);
        int points = m_livegame->points->value(p);
        int placement = 1;
        for (int j = 0; j<m_game->players->value().size();j++){
            if(i!=j){
                Player* pl = m_game->players->value(j);
                int pointsPl = m_livegame->points->value(pl);
                if(points > pointsPl){
                    placement++;
                }
            }
        }
        hash.insert(m_game->players->value(i),placement);
    }

    return hash;
}

} // namespace Database
