#include "dokolivegamecalculator.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/Doppelkopf/schmeisserei.h>
#include <Database/player.h>

#include <QDebug>

namespace Database {

DokoLiveGameCalculator::DokoLiveGameCalculator(DokoLiveGame* game):
    LiveGameCalculator(game),
    m_dokolivegame(game)
{
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_re(){
    QMap<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->players->value().size();j++){
            if(round->doko_re1PlayerId->value() == m_dokolivegame->players->value(j)->id() || round->doko_re2PlayerId->value() == m_dokolivegame->players->value(j)->id()){
                hash.insert(m_livegame->players->value(j),hash.value(m_livegame->players->value(j)) + 1);
            }
        }
    }
    return hash;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_rePercentage(){
    QMap<Player*,int> map;
    foreach(Player* p, m_dokolivegame->players->value()){
        if(m_dokolivegame->doko_rounds->value(p) > 0){
            map.insert(p,m_dokolivegame->doko_re->value(p) * 100 / m_dokolivegame->doko_rounds->value(p));
        }
        else{
            map.insert(p,0);
        }
    }
    return map;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_reWins(){
    QMap<Player*,int> hash;
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

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_reWinsPercentage() {
    QMap<Player*,int> map;
    foreach(Player* p, m_dokolivegame->players->value()){
        if(m_dokolivegame->doko_re->value(p) > 0){
            map.insert(p,m_dokolivegame->doko_reWins->value(p) * 100 / m_dokolivegame->doko_re->value(p));
        }
        else{
            map.insert(p,0);
        }
    }
    return map;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_contra(){
    QMap<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));

        for(int j = 0; j<round->currentPlayingPlayers->value().size();j++){
            if(round->doko_re1PlayerId->value() != round->currentPlayingPlayers->value(j)->id() && round->doko_re2PlayerId->value() != round->currentPlayingPlayers->value(j)->id()){
                if(round->db_state->value() == Round::FinishedState){
                    hash.insert(round->currentPlayingPlayers->value(j),hash.value(round->currentPlayingPlayers->value(j)) + 1);
                }
            }
        }
    }
    return hash;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_contraPercentage(){
    QMap<Player*,int> map;
    foreach(Player* p, m_dokolivegame->players->value()){
        if(m_dokolivegame->doko_rounds->value(p) > 0){
            map.insert(p,m_dokolivegame->doko_contra->value(p) * 100 / m_dokolivegame->doko_rounds->value(p));
        }
        else{
            map.insert(p,0);
        }
    }
    return map;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_contraWins(){
    QMap<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<round->currentPlayingPlayers->value().size();j++){
            if(round->doko_re1PlayerId->value() != round->currentPlayingPlayers->value(j)->id() && round->doko_re2PlayerId->value() != round->currentPlayingPlayers->value(j)->id()){
                if(round->points->value(round->currentPlayingPlayers->value(j)) > 0){
                    hash.insert(round->currentPlayingPlayers->value(j),hash.value(round->currentPlayingPlayers->value(j)) + 1);
                }
            }
        }
    }
    return hash;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_contraWinsPercentage() {
    QMap<Player*,int> map;
    foreach(Player* p, m_dokolivegame->players->value()){
        int totalContra = m_dokolivegame->doko_contra->value(p);
        if(totalContra > 0) {
            map.insert(p,m_dokolivegame->doko_contraWins->value(p) * 100 / m_dokolivegame->doko_contra->value(p));
        }
        else {
            map.insert(p,0);
        }
    }
    return map;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_hochzeit(){
    QMap<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->players->value().size();j++){
            if(round->doko_hochzeitPlayerId->value() == m_livegame->players->value(j)->id()){
                hash.insert(m_livegame->players->value(j),hash.value(m_livegame->players->value(j)) + 1);
            }
        }
    }
    return hash;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_solo(){
    QMap<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->players->value().size();j++){
            if(round->doko_soloPlayerId->value() == m_livegame->players->value(j)->id()){
                hash.insert(m_livegame->players->value(j),hash.value(m_livegame->players->value(j)) + 1);
            }
        }
    }
    return hash;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_trumpfabgabe(){
    QMap<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->players->value().size();j++){
            if(round->doko_trumpfabgabePlayerId->value() == m_livegame->players->value(j)->id()){
                hash.insert(m_livegame->players->value(j),hash.value(m_livegame->players->value(j)) + 1);
            }
        }
    }
    return hash;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_schweinerei(){
    QMap<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->players->value().size();j++){
            if(round->doko_schweinereiPlayerId->value() == m_livegame->players->value(j)->id()){
                hash.insert(m_livegame->players->value(j),hash.value(m_livegame->players->value(j)) + 1);
            }
        }
    }
    return hash;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_schmeisserei(){
    QMap<Player*,int> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->players->value().size();j++){
            for(int k = 0; k<round->doko_schmeissereien->value().size();k++){
                if(round->doko_schmeissereien->value(k)->playerId->value() == m_livegame->players->value(j)->id()){
                    hash.insert(m_livegame->players->value(j),hash.value(m_livegame->players->value(j)) + 1);
                }
            }
        }
    }
    return hash;
}

QMap<Player*,bool> DokoLiveGameCalculator::calculate_doko_hasPflichtSolo(){
    QMap<Player*,bool> hash;
    for(int i = 0; i<m_livegame->rounds->value().size();i++){
        DokoRound* round = static_cast<DokoRound*>(m_livegame->rounds->value(i));
        for(int j = 0; j<m_livegame->players->value().size();j++){
            if(round->doko_soloPlayerId->value() == m_livegame->players->value(j)->id() && round->doko_soloPflicht->value()){
                hash.insert(m_livegame->players->value(j),true);
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

QMap<int,int> DokoLiveGameCalculator::calculate_doko_hochzeitCountAfterRounds(){
    QMap<int,int> hash;
    for(int i = 0; i<m_dokolivegame->rounds->value().size();i++){
        int id = static_cast<DokoRound*>(m_dokolivegame->rounds->value(i))->doko_hochzeitPlayerId->value();
        int j = i+1;
        if(id>0){
            hash.insert(j,hash.value(j-1)+1);
        }
        else{
            hash.insert(j,hash.value(j-1));
        }
    }
    return hash;
}

QMap<int,int> DokoLiveGameCalculator::calculate_doko_soloCountAfterRounds(){
    QMap<int,int> hash;
    for(int i = 0; i<m_dokolivegame->rounds->value().size();i++){
        int id = static_cast<DokoRound*>(m_dokolivegame->rounds->value(i))->doko_soloPlayerId->value();
        int j = i+1;
        if(id>0){
            hash.insert(j,hash.value(j-1)+1);
        }
        else{
            hash.insert(j,hash.value(j-1));
        }
    }
    return hash;
}

QMap<int,int> DokoLiveGameCalculator::calculate_doko_pflichtSoloCountAfterRounds(){
    QMap<int,int> hash;
    for(int i = 0; i<m_dokolivegame->rounds->value().size();i++){
        int id = static_cast<DokoRound*>(m_dokolivegame->rounds->value(i))->doko_soloPlayerId->value();
        int j = i+1;
        if(id>0 && static_cast<DokoRound*>(m_dokolivegame->rounds->value(i))->doko_soloPflicht->value()){
            hash.insert(j,hash.value(j-1)+1);
        }
        else{
            hash.insert(j,hash.value(j-1));
        }
    }
    return hash;
}

QMap<int,int> DokoLiveGameCalculator::calculate_doko_trumpfabgabeCountAfterRounds(){
    QMap<int,int> hash;
    for(int i = 0; i<m_dokolivegame->rounds->value().size();i++){
        int id = static_cast<DokoRound*>(m_dokolivegame->rounds->value(i))->doko_trumpfabgabePlayerId->value();
        int j = i+1;
        if(id>0){
            hash.insert(j,hash.value(j-1)+1);
        }
        else{
            hash.insert(j,hash.value(j-1));
        }
    }
    return hash;
}

QMap<int,int> DokoLiveGameCalculator::calculate_doko_schweinereiCountAfterRounds(){
    QMap<int,int> hash;
    for(int i = 0; i<m_dokolivegame->roundCount->value();i++){
        int id = static_cast<DokoRound*>(m_dokolivegame->rounds->value(i))->doko_schweinereiPlayerId->value();
        int j = i+1;
        if(id>0){
            hash.insert(j,hash.value(j-1)+1);
        }
        else{
            hash.insert(j,hash.value(j-1));
        }
    }
    return hash;
}

QMap<int,int> DokoLiveGameCalculator::calculate_doko_schmeissereiCountAfterRounds(){
    QMap<int,int> hash;
    for(int i = 0; i<m_dokolivegame->rounds->value().size();i++){
        hash.insert(i+1,hash.value(i)+static_cast<DokoRound*>(m_dokolivegame->rounds->value(i))->doko_schmeissereien->value().size());
    }
    return hash;
}

QMap<QPair<Player*,Player*>,int> DokoLiveGameCalculator::calculate_doko_gamesTogether(){
    QMap<QPair<Player*,Player*>,int> hash;
    for(int i = 0; i<m_dokolivegame->rounds->value().size();i++){
        bool check = true;
        Round* r = m_dokolivegame->rounds->value(i);
        if (!m_dokolivegame->state->value() == Round::FinishedState){
            if(r->id() == m_dokolivegame->currentRound->value()->id()){
                check = false;
            }
        }
        if (check){
            DokoRound* round = static_cast<DokoRound*>(r);
            if(round->doko_soloPlayerId->value() == -1){
                Player* re1 = 0;
                if(round->doko_re1PlayerId->value() != -1){
                    re1 = Players::instance()->rowById(round->doko_re1PlayerId->value());
                }
                else{
                    qWarning() << "Invalid Player found in DokoLiveGameCalculator::calculate_doko_gamesTogether()!";
                    qWarning() << "RoundID: " << round->id();
                    break;
                }
                Player* re2 = 0;
                if(round->doko_re1PlayerId->value() != -1){
                    re2 = Players::instance()->rowById(round->doko_re2PlayerId->value());
                }
                else{
                    qWarning() << "Invalid Player found in DokoLiveGameCalculator::calculate_doko_gamesTogether()!";
                    qWarning() << "RoundID: " << round->id();
                    break;
                }
                Player* contra1 = 0;
                Player* contra2 = 0;
                int count = 0;
                for(int j = 0; j<r->currentPlayingPlayers->value().size();j++){
                    if(r->currentPlayingPlayers->value(j)->id() != round->doko_re2PlayerId->value() && r->currentPlayingPlayers->value(j)->id() != round->doko_re1PlayerId->value()){
                        if(count == 1){
                            contra2 = r->currentPlayingPlayers->value(j);
                            count++;
                        }
                        else if(count == 0){
                            contra1 = r->currentPlayingPlayers->value(j);
                            count++;
                        }
                    }
                }
                if(re1 != 0 && re2 != 0){
                    QPair<Player*,Player*> pair;
                    pair.first = re1;
                    pair.second = re2;
                    hash.insert(pair,hash.value(pair) + 1);
                    QPair<Player*,Player*> pair1;
                    pair1.first = re2;
                    pair1.second = re1;
                    hash.insert(pair1,hash.value(pair1) + 1);
                }
                if(contra1 !=0 && contra2 != 0){
                    QPair<Player*,Player*> pair2;
                    pair2.first = contra1;
                    pair2.second = contra2;
                    hash.insert(pair2,hash.value(pair2) + 1);
                    QPair<Player*,Player*> pair3;
                    pair3.first = contra2;
                    pair3.second = contra1;
                    hash.insert(pair3,hash.value(pair3) + 1);
                }

            }
            else{
                Player* contra1 = 0;
                Player* contra2 = 0;
                Player* contra3 = 0;
                int count = 0;
                for(int j = 0; j<r->currentPlayingPlayers->value().size();j++){
                    if(r->currentPlayingPlayers->value(j)->id() != round->doko_soloPlayerId->value()){
                        if(count == 2){
                            contra3 = r->currentPlayingPlayers->value(j);
                            count++;
                        }
                        if(count == 1){
                            contra2 = r->currentPlayingPlayers->value(j);
                            count++;
                        }
                        if(count == 0){
                            contra1 = r->currentPlayingPlayers->value(j);
                            count++;
                        }
                    }
                }

                if(contra1 !=0 && contra2 != 0 && contra3 != 0){
                    QPair<Player*,Player*> pair;
                    pair.first = contra1;
                    pair.second = contra2;
                    hash.insert(pair,hash.value(pair) + 1);
                    QPair<Player*,Player*> pair1;
                    pair1.first = contra2;
                    pair1.second = contra1;
                    hash.insert(pair1,hash.value(pair1) + 1);
                    QPair<Player*,Player*> pair2;
                    pair2.first = contra1;
                    pair2.second = contra3;
                    hash.insert(pair2,hash.value(pair2) + 1);
                    QPair<Player*,Player*> pair3;
                    pair3.first = contra3;
                    pair3.second = contra1;
                    hash.insert(pair3,hash.value(pair3) + 1);
                    QPair<Player*,Player*> pair4;
                    pair4.first = contra3;
                    pair4.second = contra2;
                    hash.insert(pair4,hash.value(pair4) + 1);
                    QPair<Player*,Player*> pair5;
                    pair5.first = contra2;
                    pair5.second = contra3;
                    hash.insert(pair5,hash.value(pair5) + 1);
                }
            }
        }
    }
    return hash;
}

QMap<QPair<Player*,Player*>,int> DokoLiveGameCalculator::calculate_doko_winsTogether(){
    QMap<QPair<Player*,Player*>,int> hash;
    for(int i = 0; i<m_dokolivegame->rounds->value().size();i++){
        bool check = true;
        Round* r = m_dokolivegame->rounds->value(i);
        if (!m_dokolivegame->state->value() == Round::FinishedState){
            if(r->id() == m_dokolivegame->currentRound->value()->id()){
                check = false;
            }
        }
        if (check){
            DokoRound* round = static_cast<DokoRound*>(r);
            if(round->doko_soloPlayerId->value() == -1){
                Player* re1 = 0;
                if(round->doko_re1PlayerId->value() != -1){
                    re1 = Players::instance()->rowById(round->doko_re1PlayerId->value());
                }
                else{
                    qWarning() << "Invalid Player found in DokoLiveGameCalculator::calculate_doko_winsTogether()!";
                    qWarning() << "RoundID: " << round->id();
                    break;
                }
                Player* re2 = 0;
                if(round->doko_re1PlayerId->value() != -1){
                    re2 = Players::instance()->rowById(round->doko_re2PlayerId->value());
                }
                else{
                    qWarning() << "Invalid Player found in DokoLiveGameCalculator::calculate_doko_winsTogether()!";
                    qWarning() << "RoundID: " << round->id();
                    break;
                }
                if(round->points->value(re1) > 0 && round->points->value(re2) > 0){
                    if(re1 != 0 && re2 != 0){
                        QPair<Player*,Player*> pair;
                        pair.first = re1;
                        pair.second = re2;
                        hash.insert(pair,hash.value(pair) + 1);
                        QPair<Player*,Player*> pair1;
                        pair1.first = re2;
                        pair1.second = re1;
                        hash.insert(pair1,hash.value(pair1) + 1);
                    }
                }
                else{
                    Player* contra1 = 0;
                    Player* contra2 = 0;
                    int count = 0;
                    for(int j = 0; j<r->currentPlayingPlayers->value().size();j++){
                        if(r->currentPlayingPlayers->value(j)->id() != round->doko_re2PlayerId->value() && r->currentPlayingPlayers->value(j)->id() != round->doko_re1PlayerId->value()){
                            if(count == 1){
                                contra2 = r->currentPlayingPlayers->value(j);
                                count++;
                            }
                            else if(count == 0){
                                contra1 = r->currentPlayingPlayers->value(j);
                                count++;
                            }
                        }
                    }
                    if(contra1 !=0 && contra2 != 0){
                        QPair<Player*,Player*> pair2;
                        pair2.first = contra1;
                        pair2.second = contra2;
                        hash.insert(pair2,hash.value(pair2) + 1);
                        QPair<Player*,Player*> pair3;
                        pair3.first = contra2;
                        pair3.second = contra1;
                        hash.insert(pair3,hash.value(pair3) + 1);
                    }
                }

            }
            else{
                if(round->points->value(Players::instance()->rowById(round->doko_re1PlayerId->value())) < 0){
                    Player* contra1 = 0;
                    Player* contra2 = 0;
                    Player* contra3 = 0;
                    int count = 0;
                    for(int j = 0; j<r->currentPlayingPlayers->value().size();j++){
                        if(r->currentPlayingPlayers->value(j)->id() != round->doko_soloPlayerId->value()){
                            if(count == 2){
                                contra3 = r->currentPlayingPlayers->value(j);
                                count++;
                            }
                            if(count == 1){
                                contra2 = r->currentPlayingPlayers->value(j);
                                count++;
                            }
                            if(count == 0){
                                contra1 = r->currentPlayingPlayers->value(j);
                                count++;
                            }
                        }
                    }
                    if(contra1 !=0 && contra2 != 0 && contra3 != 0){
                        QPair<Player*,Player*> pair;
                        pair.first = contra1;
                        pair.second = contra2;
                        hash.insert(pair,hash.value(pair) + 1);
                        QPair<Player*,Player*> pair1;
                        pair1.first = contra2;
                        pair1.second = contra1;
                        hash.insert(pair1,hash.value(pair1) + 1);
                        QPair<Player*,Player*> pair2;
                        pair2.first = contra1;
                        pair2.second = contra3;
                        hash.insert(pair2,hash.value(pair2) + 1);
                        QPair<Player*,Player*> pair3;
                        pair3.first = contra3;
                        pair3.second = contra1;
                        hash.insert(pair3,hash.value(pair3) + 1);
                        QPair<Player*,Player*> pair4;
                        pair4.first = contra3;
                        pair4.second = contra2;
                        hash.insert(pair4,hash.value(pair4) + 1);
                        QPair<Player*,Player*> pair5;
                        pair5.first = contra2;
                        pair5.second = contra3;
                        hash.insert(pair5,hash.value(pair5) + 1);
                    }
                }
            }
        }
    }
    return hash;
}

QMap<Player*,double> DokoLiveGameCalculator::calculate_doko_pointAveragePerWin(){
    QMap<Player*,double> hash;
    for(int j = 0; j<m_dokolivegame->players->value().size();j++){
        int points = 0;
        for(int i = 0; i<m_dokolivegame->rounds->value().size();i++){
            if(m_dokolivegame->rounds->value(i)->points->value(m_dokolivegame->players->value(j)) > 0){
                points += m_dokolivegame->rounds->value(i)->points->value(m_dokolivegame->players->value(j));
            }
        }
        hash.insert(m_dokolivegame->players->value(j),(double)points/(double)m_dokolivegame->doko_roundWins->value(m_dokolivegame->players->value(j)));
    }
    return hash;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_rounds(){
    QMap<Player*,int> hash;
    foreach(Round* r, m_dokolivegame->rounds->value()){
        foreach(Player* p, r->currentPlayingPlayers->value()){
            hash.insert(p,hash.value(p)+1);
        }
    }
    return hash;
}

QMap<Player*,int> DokoLiveGameCalculator::calculate_doko_roundWins(){
    QMap<Player*,int> hash;
    for(int i = 0; i<m_dokolivegame->rounds->value().size();i++){
        foreach(Player* p, m_dokolivegame->players->value()){
            if(m_dokolivegame->rounds->value(i)->points->value(p) > 0){
                hash.insert(p,hash.value(p)+1);
            }
        }
    }
    return hash;
}

QMap<Player*,double> DokoLiveGameCalculator::calculate_doko_roundWinsPercentage(){
    QMap<Player*,double> hash;
    foreach(Player* p, m_dokolivegame->players->value()){
        if(m_dokolivegame->doko_rounds->value(p) > 0){
            hash.insert(p,(double)m_dokolivegame->doko_roundWins->value(p) * 100.0 /(double)m_dokolivegame->doko_rounds->value(p));
        }
    }
    return hash;
}

QMap<int,QMap<Player*,int> > DokoLiveGameCalculator::calculate_placementAfterRounds(){
    QMap<int,QMap<Player*,int> > hash;

    QMap<Player*,int> points;
    int count = 0;
    foreach(Round* r, m_livegame->rounds->value()){
        if(r->state->value() == Round::FinishedState){
            foreach(Player* p, m_livegame->players->value()){
                points.insert(p,points.value(p)+r->points->value(p));
            }
            QMap<Player*,int> placement;
            foreach(Player* p, m_livegame->players->value()){
                int place = 1;
                foreach(Player* q, m_livegame->players->value()){
                    if(p->id() != q->id()){
                        if(points.value(p) < points.value(q)){
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

QString DokoLiveGameCalculator::calculate_doko_hochzeitStats()
{
    //    int count = m_dokolivegame->doko_hochzeitCount->value();
    int roundCount = m_dokolivegame->roundCount->value();
    int countAfterRounds = m_dokolivegame->doko_hochzeitCountAfterRounds->value(roundCount);
    if(roundCount > 0)
    {
        //qDebug() << countAfterRounds << " / " << roundCount;
        int percentage = countAfterRounds * 100 / roundCount;
        int position = m_dokolivegame->doko_hochzeitPositionAfterRounds->value(m_dokolivegame->roundCount->value());
        return "(" + QString::number(percentage) + "% | " + QString::number(position) + ".)";
    }

    return QString();
}

QString DokoLiveGameCalculator::calculate_doko_soloStats()
{
    //    int count = m_dokolivegame->doko_hochzeitCount->value();
    int roundCount = m_dokolivegame->roundCount->value();
    int countAfterRounds = m_dokolivegame->doko_soloCountAfterRounds->value(roundCount);
    if(roundCount > 0)
    {
        int percentage = countAfterRounds * 100 / roundCount;
        int position = m_dokolivegame->doko_soloPositionAfterRounds->value(m_dokolivegame->roundCount->value());
        return "(" + QString::number(percentage) + "% | " + QString::number(position) + ".)";
    }

    return QString();
}
QString DokoLiveGameCalculator::calculate_doko_pflichtSoloStats()
{
    //    int count = m_dokolivegame->doko_hochzeitCount->value();
    int roundCount = m_dokolivegame->roundCount->value();
    int countAfterRounds = m_dokolivegame->doko_pflichtSoloCountAfterRounds->value(roundCount);
    if(roundCount > 0)
    {
        int percentage = countAfterRounds * 100 / roundCount;
        int position = m_dokolivegame->doko_pflichtSoloPositionAfterRounds->value(m_dokolivegame->roundCount->value());
        return "(" + QString::number(percentage) + "% | " + QString::number(position) + ".)";
    }

    return QString();
}

QString DokoLiveGameCalculator::calculate_doko_trumpfabgabeStats()
{
    //    int count = m_dokolivegame->doko_hochzeitCount->value();
    int roundCount = m_dokolivegame->roundCount->value();
    int countAfterRounds = m_dokolivegame->doko_trumpfabgabeCountAfterRounds->value(roundCount);
    if(roundCount > 0)
    {
        int percentage = countAfterRounds * 100 / roundCount;
        int position = m_dokolivegame->doko_trumpfabgabePositionAfterRounds->value(m_dokolivegame->roundCount->value());
        return "(" + QString::number(percentage) + "% | " + QString::number(position) + ".)";
    }

    return QString();
}

QString DokoLiveGameCalculator::calculate_doko_schweinereiStats()
{
    //    int count = m_dokolivegame->doko_hochzeitCount->value();
    int roundCount = m_dokolivegame->roundCount->value();
    int countAfterRounds = m_dokolivegame->doko_schweinereiCountAfterRounds->value(roundCount);
    if(roundCount > 0)
    {
        int percentage = countAfterRounds * 100 / roundCount;
        int position = m_dokolivegame->doko_schweinereiPositionAfterRounds->value(m_dokolivegame->roundCount->value());
        return "(" + QString::number(percentage) + "% | " + QString::number(position) + ".)";
    }

    return QString();
}

QString DokoLiveGameCalculator::calculate_doko_reVsContraStats(){
    return QString::number(m_dokolivegame->doko_reRoundWins->value()) + " : " + QString::number(m_dokolivegame->doko_contraRoundWins->value());
}

QString DokoLiveGameCalculator::calculate_doko_contraVsContraStats(){

}

QString DokoLiveGameCalculator::calculate_doko_schmeissereiStats()
{
    //    int count = m_dokolivegame->doko_hochzeitCount->value();
    int roundCount = m_dokolivegame->roundCount->value();
    int countAfterRounds = m_dokolivegame->doko_schmeissereiCountAfterRounds->value(m_dokolivegame->rounds->value().size());
    if(roundCount > 0)
    {
        int percentage = countAfterRounds * 100 / m_dokolivegame->roundCount->value();
        int position = m_dokolivegame->doko_schmeissereiPositionAfterRounds->value(m_dokolivegame->rounds->value().size());
        return "(" + QString::number(percentage) + "% | " + QString::number(position) + ".)";
    }

    return QString();
}

QMap<int,int> DokoLiveGameCalculator::calculate_doko_hochzeitPositionAfterRounds() {
    QMap<int,int> map;
    for(int i = 0; i<m_dokolivegame->roundCount->value();i++){
        int count = 1;
        int percThis = m_dokolivegame->doko_hochzeitCountAfterRounds->value(i+1) *100 / (i+1);
        foreach(Game* g, Games::instance()->gamesOfType->value("Doppelkopf")){
            if(g->live->value()){
                DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
                int percentage = 0;
                if(i+1 <= game->roundCount->value()){ // Wenn die Zahl der Runden des Spiels größer sind als der aktuelle Runden-Count
                    percentage = game->doko_hochzeitCountAfterRounds->value(i+1) * 100 / (i+1);
                }
                else if(game->roundCount->value() > 0){ // Sonst soll er den Wert zum Abschluss des Spiels nehmen
                    percentage = game->doko_hochzeitCountAfterRounds->value(game->roundCount->value()) * 100 / game->roundCount->value();
                }
                if(percentage > percThis){
                    count++;
                }
            }
        }
        map.insert(i+1,count);
    }
    return map;
}

QMap<int,int> DokoLiveGameCalculator::calculate_doko_soloPositionAfterRounds(){
    QMap<int,int> map;
    for(int i = 0; i<m_dokolivegame->roundCount->value();i++){
        int count = 1;
        int percThis = m_dokolivegame->doko_soloCountAfterRounds->value(i+1) *100 / (i+1);
        foreach(Game* g, Games::instance()->gamesOfType->value("Doppelkopf")){
            if(g->live->value()){
                DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
                int percentage = 0;
                if(i+1 <= game->roundCount->value()){
                    percentage = game->doko_soloCountAfterRounds->value(i+1) * 100 / (i+1);
                }
                else if(game->roundCount->value() > 0){
                    percentage = game->doko_soloCountAfterRounds->value(game->roundCount->value()) * 100 / game->roundCount->value();
                }
                if(percentage > percThis){
                    count++;
                }
            }
        }
        map.insert(i+1,count);
    }
    return map;
}

QMap<int,int> DokoLiveGameCalculator::calculate_doko_trumpfabgabePositionAfterRounds(){
    QMap<int,int> map;
    for(int i = 0; i<m_dokolivegame->roundCount->value();i++){
        int count = 1;
        int percThis = m_dokolivegame->doko_trumpfabgabeCountAfterRounds->value(i+1) *100 / (i+1);
        foreach(Game* g, Games::instance()->gamesOfType->value("Doppelkopf")){
            if(g->live->value()){
                DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
                int percentage = 0;
                if(i+1 <= game->roundCount->value()){
                    percentage = game->doko_trumpfabgabeCountAfterRounds->value(i+1) * 100 / (i+1);
                }
                else if(game->roundCount->value() > 0){
                    percentage = game->doko_trumpfabgabeCountAfterRounds->value(game->roundCount->value()) * 100 / game->roundCount->value();
                }
                if(percentage > percThis){
                    count++;
                }
            }
        }
        map.insert(i+1,count);
    }
    return map;
}

QMap<int,int> DokoLiveGameCalculator::calculate_doko_pflichtSoloPositionAfterRounds(){
    QMap<int,int> map;
    for(int i = 0; i<m_dokolivegame->roundCount->value();i++){
        int count = 1;
        int percThis = m_dokolivegame->doko_pflichtSoloCountAfterRounds->value(i+1) *100 / (i+1);
        foreach(Game* g, Games::instance()->gamesOfType->value("Doppelkopf")){
            if(g->live->value()){
                DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
                int percentage = 0;
                if(i+1 <= game->roundCount->value()){
                    percentage = game->doko_pflichtSoloCountAfterRounds->value(i+1) * 100 / (i+1);
                }
                else if(game->roundCount->value() > 0){
                    percentage = game->doko_pflichtSoloCountAfterRounds->value(game->roundCount->value()) * 100 / game->roundCount->value();
                }
                if(percentage > percThis){
                    count++;
                }
            }
        }
        map.insert(i+1,count);
    }
    return map;
}

QMap<int,int> DokoLiveGameCalculator::calculate_doko_schmeissereiPositionAfterRounds(){
    QMap<int,int> map;
    for(int i = 0; i<m_dokolivegame->rounds->value().size();i++){
        int count = 1;
        int percThis = m_dokolivegame->doko_schmeissereiCountAfterRounds->value(i+1) *100 / (i+1);
        foreach(Game* g, Games::instance()->gamesOfType->value("Doppelkopf")){
            if(g->live->value()){
                DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
                int percentage = 0;
                if(i+1 <= game->roundCount->value()){
                    percentage = game->doko_schmeissereiCountAfterRounds->value(i+1) * 100 / (i+1);
                }
                else if(game->roundCount->value() > 0){
                    percentage = game->doko_schmeissereiCountAfterRounds->value(game->roundCount->value()) * 100 / game->roundCount->value();
                }
                if(percentage > percThis){
                    count++;
                }
            }
        }
        map.insert(i+1,count);
    }
    return map;
}

QMap<int,int> DokoLiveGameCalculator::calculate_doko_schweinereiPositionAfterRounds(){
    QMap<int,int> map;
    for(int i = 0; i<m_dokolivegame->roundCount->value();i++){
        int count = 1;
        int percThis = m_dokolivegame->doko_schweinereiCountAfterRounds->value(i+1) *100 / (i+1);
        foreach(Game* g, Games::instance()->gamesOfType->value("Doppelkopf")){
            if(g->live->value()){
                DokoLiveGame* game = static_cast<DokoLiveGame*>(g);
                int percentage = 0;
                if(i+1 <= game->roundCount->value()){
                    percentage = game->doko_schweinereiCountAfterRounds->value(i+1) * 100 / (i+1);
                }
                else if(game->roundCount->value() > 0){
                    percentage = game->doko_schweinereiCountAfterRounds->value(game->roundCount->value()) * 100 / game->roundCount->value();
                }
                if(percentage > percThis){
                    count++;
                }
            }
        }
        map.insert(i+1,count);
    }
    return map;
}

int DokoLiveGameCalculator::calculate_doko_reRoundWins(){
    int count = 0;
    foreach(Round* r, m_dokolivegame->rounds->value()){
        DokoRound* dokoRound = static_cast<DokoRound*>(r);
        if(dokoRound->points->value(Players::instance()->rowById(dokoRound->doko_re1PlayerId->value())) > 0){
            count++;
        }
    }
    return count;
}

int DokoLiveGameCalculator::calculate_doko_contraRoundWins(){
    int count = 0;
    foreach(Round* r, m_dokolivegame->rounds->value()){
        DokoRound* dokoRound = static_cast<DokoRound*>(r);
        if(dokoRound->points->value(Players::instance()->rowById(dokoRound->doko_re1PlayerId->value())) < 0){
            count++;
        }
    }
    return count;
}



} // namespace Database
