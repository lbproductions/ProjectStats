#ifndef ROUNDCALCULATOR_H
#define ROUNDCALCULATOR_H

#include <QPointer>

#include <Database/attributehash.h>
#include <Database/attributelist.h>

namespace Database {

class Round;
class Player;

class RoundCalculator : public QObject
{
    Q_OBJECT
public:
    RoundCalculator(Round* round);

    AttributeHash<Player*,int> calculate_points();

    virtual int calculate_cardmixerPosition();

    virtual int calculate_roundPoints();

    virtual AttributeList<Player*> calculate_currentPlayingPlayers();

protected:
    QPointer<Round> m_round;
};

}

#endif // ROUNDCALCULATOR_H
