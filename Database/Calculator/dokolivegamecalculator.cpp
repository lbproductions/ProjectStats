#include "dokolivegamecalculator.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>

#include <QDebug>

namespace Database {

DokoLiveGameCalculator::DokoLiveGameCalculator(DokoLiveGame* game):
    LiveGameCalculator(game),
    m_dokolivegame(game)
{
}

AttributeHash<Player*,int> DokoLiveGameCalculator::calculate_doko_re(){
    AttributeHash<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        qDebug() << round->gameId->value();
        for(int j = 0; j<m_livegame->players->value().size();j++){
            if(round->doko_re1PlayerId->value() == m_livegame->players->value(j)->id() || round->doko_re2PlayerId->value() == m_livegame->players->value(j)->id()){
                hash.insert(m_livegame->players->value(j),hash.value(m_livegame->players->value(j)) + 1);
            }
        }
    }
    return hash;
}

AttributeHash<Player*,int> DokoLiveGameCalculator::calculate_doko_reWins(){
    AttributeHash<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        qDebug() << round->gameId->value();
        for(int j = 0; j<m_livegame->players->value().size();j++){
            if(round->doko_re1PlayerId->value() == m_livegame->players->value(j)->id() || round->doko_re2PlayerId->value() == m_livegame->players->value(j)->id()){
                if(round->points->value(m_livegame->players->value(j)) > 0){
                    hash.insert(m_livegame->players->value(j),hash.value(m_livegame->players->value(j)) + 1);
                }
            }
        }
    }
    return hash;
}

int DokoLiveGameCalculator::calculate_totalPoints(){
    int count = 0;
    for(int i = 0; i<m_dokolivegame->rounds->value().size();i++){
        count += m_dokolivegame->rounds->value(i)->roundPoints->value();
    }
    return count;
}

} // namespace Database
