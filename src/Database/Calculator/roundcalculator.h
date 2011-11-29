#ifndef ROUNDCALCULATOR_H
#define ROUNDCALCULATOR_H

#include <QMap>
#include <QObject>

namespace Database {

class Round;
class Player;
class Point;

class RoundCalculator : public QObject
{
    Q_OBJECT
public:
    RoundCalculator(Round* round);

    QMap<Player*,Point*> calculate_points();

    virtual int calculate_cardmixerPosition();

    virtual int calculate_roundPoints();

    virtual QList<Player*> calculate_currentPlayingPlayers();

protected:
    Round* m_round;
};

}

#endif // ROUNDCALCULATOR_H
