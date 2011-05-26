#ifndef DATABASE_DOKOROUNDCALCULATOR_H
#define DATABASE_DOKOROUNDCALCULATOR_H

#include <Database/Calculator/roundcalculator.h>

namespace Database {

class DokoRound;
class Player;

class DokoRoundCalculator : public RoundCalculator
{
public:
    DokoRoundCalculator(DokoRound* round);

    AttributeList<Player*> calculate_currentPlayingPlayers();

    int calculate_roundPoints();

private:
    QPointer<DokoRound> m_dokoround;
};

} // namespace Database

#endif // DATABASE_DOKOROUNDCALCULATOR_H
