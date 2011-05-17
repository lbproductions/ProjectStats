#ifndef ROUNDCALCULATOR_H
#define ROUNDCALCULATOR_H

#include <QPointer>

#include <Database/attributehash.h>

namespace Database {

class Round;
class Player;

class RoundCalculator : public QObject
{
    Q_OBJECT
public:
    RoundCalculator(Round* round);

    AttributeHash<Player*,int> calculate_points();

private:

    QPointer<Round> m_round;
};

}

#endif // ROUNDCALCULATOR_H
