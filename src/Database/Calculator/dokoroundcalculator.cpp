#include "dokoroundcalculator.h"

#include <Database/player.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/Doppelkopf/schmeisserei.h>

namespace Database {

DokoRoundCalculator::DokoRoundCalculator(DokoRound* round):
    RoundCalculator(round),
    m_dokoround(round)
{
}

QList<Player*> DokoRoundCalculator::calculate_currentPlayingPlayers(){
    QPointer<DokoLiveGame> game = static_cast<DokoLiveGame*>(m_dokoround->game->value());

        QList<Player*> players;
        if(game->playersSortedByPosition->value().isEmpty())
        {
            return players;
        }

        int anzPlayers = game->playersSortedByPosition->value().size();
        for(int i = m_round->cardmixerPosition->value()+1, anzahl = 0; anzahl < 4; i++, anzahl++)
        {
            i = i % anzPlayers;

            if(anzPlayers > 5 && anzahl+1 == anzPlayers / 2)
            {
                ++i;
            }

            i = i % anzPlayers;

            Player *player = game->playersSortedByPosition->value(i);
            players.append(player);
        }

        return players;
}

int DokoRoundCalculator::calculate_roundPoints()
{
    int soloId = m_dokoround->doko_soloPlayerId->value();
    if(soloId > 0)
    {
        return qAbs(m_dokoround->points->value(Players::instance()->rowById(soloId)) / 3);
    }

    return qAbs(m_dokoround->points->value(Players::instance()->rowById(m_dokoround->doko_re1PlayerId->value())));
}

QList<Schmeisserei*> DokoRoundCalculator::calculate_doko_schmeissereien(){
    QList<Schmeisserei*> list;
    foreach(Schmeisserei* s, Schmeissereis::instance()->allRows()){
        if(s->roundId->value() == m_dokoround->id()){
            list.append(s);
        }
    }
    return list;
}

QMap<Player*,bool> DokoRoundCalculator::calculate_doko_re(){
    QMap<Player*,bool> hash;
    for(int i = 0; i<m_dokoround->currentPlayingPlayers->value().size();i++){
        if(m_dokoround->currentPlayingPlayers->value(i)->id() == m_dokoround->doko_re1PlayerId->value() ||
                m_dokoround->currentPlayingPlayers->value(i)->id() == m_dokoround->doko_re2PlayerId->value()){
            hash.insert(m_dokoround->currentPlayingPlayers->value(i),true);
        }
        else{
            hash.insert(m_dokoround->currentPlayingPlayers->value(i),false);
        }
    }
    return hash;
}

QList<Player*> DokoRoundCalculator::calculate_doko_winningPlayers()
{
    QList<Player*> list;
    foreach(Player* player, m_dokoround->currentPlayingPlayers->value()){
        if(m_dokoround->points->value(player) > 0){
            list.append(player);
        }
    }
    return list;
}

QList<QList<Player*> > DokoRoundCalculator::calculate_doko_togetherPlayingPlayers(){
    QList<QList<Player*> > lists;

    if(m_dokoround->doko_soloPlayerId->value() > 0){    // we have a solo
        QList<Player*> soloPlayer;
        soloPlayer.append(Players::instance()->rowById(m_dokoround->doko_soloPlayerId->value()));
        lists.append(soloPlayer);

        QList<Player*> rest;
        foreach(Player* player, m_dokoround->currentPlayingPlayers->value()){
            if(player->id() != m_dokoround->doko_soloPlayerId->value()){
                rest.append(player);
            }
        }
        lists.append(rest);
    }

    else{   // normal game
        QList<Player*> contraPlayers = m_dokoround->currentPlayingPlayers->value();
        QList<Player*> rePlayers;
        foreach(Player* player, contraPlayers)
        {
            if(m_dokoround->doko_re->value(player)){
                contraPlayers.removeOne(player);
                rePlayers.append(player);
            }
        }
        lists.append(contraPlayers);
        lists.append(rePlayers);
    }

    return lists;
}

} // namespace Database
