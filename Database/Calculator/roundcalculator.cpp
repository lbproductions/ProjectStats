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

QList<Point*> RoundCalculator::calculate_pointInstances()
{
    return Points::instance()->rowsBySqlCondition(QLatin1String("WHERE roundId = ")+QString::number(m_round->id()));
}

QMap<Player*,int> RoundCalculator::calculate_points(){
    QMap<Player*,int> hash;
    QList<Point*> points = m_round->pointInstances->value();
    foreach(Point* p, points)
    {
        hash.insert(Players::instance()->rowById(p->playerId->value()),
                    p->points->value());
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
