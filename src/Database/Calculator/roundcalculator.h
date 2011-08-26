#ifndef ROUNDCALCULATOR_H
#define ROUNDCALCULATOR_H

#include <QPointer>

#include <QMap>

namespace Database {

class Round;
class Player;
class Point;

class RoundCalculator : public QObject
{
    Q_OBJECT
public:
    RoundCalculator(Round* round);

    QMap<Player*,int> calculate_points();

    QMap<Player*,Point*> calculate_pointObjects();

    virtual int calculate_cardmixerPosition();

    virtual int calculate_roundPoints();

    QList<Point*> calculate_pointInstances();

    virtual QList<Player*> calculate_currentPlayingPlayers();

protected:
    QPointer<Round> m_round;
};

}

#endif // ROUNDCALCULATOR_H
