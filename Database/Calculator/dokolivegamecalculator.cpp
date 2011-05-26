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

AttributeHash<Player*,int> DokoLiveGameCalculator::calculate_doko_contra(){
    AttributeHash<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->currentPlayingPlayers->value().size();j++){
            if(round->doko_re1PlayerId->value() != m_livegame->currentPlayingPlayers->value(j)->id() && round->doko_re2PlayerId->value() != m_livegame->currentPlayingPlayers->value(j)->id()){
                hash.insert(m_livegame->currentPlayingPlayers->value(j),hash.value(m_livegame->currentPlayingPlayers->value(j)) + 1);
            }
        }
    }
    return hash;
}

AttributeHash<Player*,int> DokoLiveGameCalculator::calculate_doko_contraWins(){
    AttributeHash<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->currentPlayingPlayers->value().size();j++){
            if(round->doko_re1PlayerId->value() != m_livegame->currentPlayingPlayers->value(j)->id() && round->doko_re2PlayerId->value() != m_livegame->currentPlayingPlayers->value(j)->id()){
                if(round->points->value(m_livegame->currentPlayingPlayers->value(j)) > 0){
                    hash.insert(m_livegame->currentPlayingPlayers->value(j),hash.value(m_livegame->currentPlayingPlayers->value(j)) + 1);
                }
            }
        }
    }
    return hash;
}

AttributeHash<Player*,int> DokoLiveGameCalculator::calculate_doko_hochzeit(){
    AttributeHash<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->currentPlayingPlayers->value().size();j++){
            if(round->doko_hochzeitPlayerId->value() == m_livegame->currentPlayingPlayers->value(i)->id()){
                hash.insert(m_livegame->currentPlayingPlayers->value(j),hash.value(m_livegame->currentPlayingPlayers->value(j)) + 1);
            }
        }
    }
    return hash;
}

AttributeHash<Player*,int> DokoLiveGameCalculator::calculate_doko_solo(){
    AttributeHash<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->currentPlayingPlayers->value().size();j++){
            if(round->doko_soloPlayerId->value() == m_livegame->currentPlayingPlayers->value(i)->id()){
                hash.insert(m_livegame->currentPlayingPlayers->value(j),hash.value(m_livegame->currentPlayingPlayers->value(j)) + 1);
            }
        }
    }
    return hash;
}

AttributeHash<Player*,int> DokoLiveGameCalculator::calculate_doko_trumpfabgabe(){
    AttributeHash<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->currentPlayingPlayers->value().size();j++){
            if(round->doko_trumpfabgabePlayerId->value() == m_livegame->currentPlayingPlayers->value(i)->id()){
                hash.insert(m_livegame->currentPlayingPlayers->value(j),hash.value(m_livegame->currentPlayingPlayers->value(j)) + 1);
            }
        }
    }
    return hash;
}

AttributeHash<Player*,int> DokoLiveGameCalculator::calculate_doko_schweinerei(){
    AttributeHash<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->currentPlayingPlayers->value().size();j++){
            if(round->doko_schweinereiPlayerId->value() == m_livegame->currentPlayingPlayers->value(i)->id()){
                hash.insert(m_livegame->currentPlayingPlayers->value(j),hash.value(m_livegame->currentPlayingPlayers->value(j)) + 1);
            }
        }
    }
    return hash;
}

AttributeHash<Player*,int> DokoLiveGameCalculator::calculate_doko_schmeisserei(){
    AttributeHash<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->currentPlayingPlayers->value().size();j++){
            if(round->doko_hochzeitPlayerId->value() == m_livegame->currentPlayingPlayers->value(i)->id()){
                hash.insert(m_livegame->currentPlayingPlayers->value(j),hash.value(m_livegame->currentPlayingPlayers->value(j)) + 1);
            }
        }
    }
    return hash;
}

AttributeHash<Player*,bool> DokoLiveGameCalculator::calculate_doko_hasPflichtSolo(){
    AttributeHash<Player*,bool> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->currentPlayingPlayers->value().size();j++){
            if(round->doko_soloPlayerId->value() == m_livegame->currentPlayingPlayers->value(i)->id() && round->doko_soloPflicht->value()){
                hash.insert(m_livegame->currentPlayingPlayers->value(j),true);
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

int DokoLiveGameCalculator::calculate_doko_hochzeitCount(){
    int count = 0;
    for(int i = 0; i<m_dokolivegame->players->value().size();i++){
        count += m_dokolivegame->doko_hochzeit->value(m_dokolivegame->players->value(i));
    }
    return count;
}

int DokoLiveGameCalculator::calculate_doko_soloCount(){
    int count = 0;
    for(int i = 0; i<m_dokolivegame->players->value().size();i++){
        count += m_dokolivegame->doko_solo->value(m_dokolivegame->players->value(i));
    }
    return count;
}

int DokoLiveGameCalculator::calculate_doko_pflichtSoloCount(){
    int count = 0;
    for(int i = 0; i<m_dokolivegame->players->value().size();i++){
        if(m_dokolivegame->doko_hasPflichtSolo->value(m_dokolivegame->players->value(i))){
            count++;
        }
    }
    return count;
}

int DokoLiveGameCalculator::calculate_doko_trumpfabgabeCount(){
    int count = 0;
    for(int i = 0; i<m_dokolivegame->players->value().size();i++){
        count += m_dokolivegame->doko_trumpfabgabe->value(m_dokolivegame->players->value(i));
    }
    return count;
}

int DokoLiveGameCalculator::calculate_doko_schweinereiCount(){
    int count = 0;
    for(int i = 0; i<m_dokolivegame->players->value().size();i++){
        count += m_dokolivegame->doko_schweinerei->value(m_dokolivegame->players->value(i));
    }
    return count;
}

int DokoLiveGameCalculator::calculate_doko_schmeissereiCount(){
    int count = 0;
    for(int i = 0; i<m_dokolivegame->players->value().size();i++){
        count += m_dokolivegame->doko_schmeisserei->value(m_dokolivegame->players->value(i));
    }
    return count;
}

} // namespace Database
