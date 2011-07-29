#include "roundcalculator.h"

#include <Database/player.h>
#include <Database/round.h>
#include <Database/point.h>
#include <Database/livegame.h>

#include <QObject>

using namespace Database;

RoundCalculator::RoundCalculator(Round* round):
    QObject(round),
    m_round(round)
{
}

QMap<Player*,int> RoundCalculator::calculate_points(){
    QMap<Player*,int> hash;
    foreach(Point* p,Points::instance()->allRows()){
        if(p->roundId->value() == m_round->id()){
            hash.insert(Players::instance()->rowById(p->playerId->value()),
                        p->points->value());
        }
    }
    return hash;
}

int RoundCalculator::calculate_cardmixerPosition(){
    QPointer<LiveGame> game = (LiveGame*)m_round->game->value().data();

    if(game->playersSortedByPosition->value().isEmpty())
    {
        return 0;
    }

    return (m_round->number->value()) % game->playersSortedByPosition->value().size();
}

QList<Player*> RoundCalculator::calculate_currentPlayingPlayers(){
    return m_round->game->value()->playersSortedByPosition->value();
}

int RoundCalculator::calculate_roundPoints(){
    return 0;
}
