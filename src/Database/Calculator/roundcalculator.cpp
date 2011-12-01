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

QMap<Player*,Point*> RoundCalculator::calculate_points() {
    QMap<Player*,Point*> hash;
    QList<Point*> points = Points::instance()->rowsBySqlCondition(QLatin1String("WHERE roundId = ")+QString::number(m_round->id()));
    foreach(Point* p, points)
    {
        if(p)
        {
            p->points->addDependingAttribute(m_round->points);
            hash.insert(Players::instance()->castedRowById(p->playerId->value()),
                        p);
        }
    }
    return hash;
}

int RoundCalculator::calculate_cardmixerPosition(){
    LiveGame* game = static_cast<LiveGame*>(m_round->game->value());

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
