#include "skatlivegamecalculator.h"

#include "../Skat/skatlivegame.h"
#include "../point.h"
#include "../player.h"

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

QMap<int,QMap<Player*,int> > SkatLiveGameCalculator::calculate_placementAfterRounds(){
    QMap<int,QMap<Player*,int> > hash;

    QMap<Player*,int> points;
    int count = 0;
    foreach(Round* r, m_livegame->rounds->value()){
        if(r->state->value() == Round::FinishedState){
            foreach(Player* p, m_livegame->players->value()){
                points.insert(p,points.value(p)+r->points->value(p)->points->value());
            }
            QMap<Player*,int> placement;
            foreach(Player* p, m_livegame->players->value()){
                int place = 1;
                foreach(Player* q, m_livegame->players->value()){
                    if(p->id() != q->id()){
                        if(points.value(p) > points.value(q)){
                            place++;
                        }
                    }
                }
                placement.insert(p,place);
            }
            hash.insert(count,placement);
            count++;
        }
    }
    return hash;
}

} // namespace Database
