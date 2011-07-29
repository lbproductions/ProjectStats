#ifndef DATABASE_DOKOROUNDCALCULATOR_H
#define DATABASE_DOKOROUNDCALCULATOR_H

#include <Database/Calculator/roundcalculator.h>

namespace Database {

class DokoRound;
class Player;
class Schmeisserei;

class DokoRoundCalculator : public RoundCalculator
{
public:
    DokoRoundCalculator(DokoRound* round);

    QList<Player*> calculate_currentPlayingPlayers();

    int calculate_roundPoints();

    QList<Schmeisserei*> calculate_doko_schmeissereien();

    QMap<Player*,bool> calculate_doko_re();

private:
    QPointer<DokoRound> m_dokoround;
};

} // namespace Database

#endif // DATABASE_DOKOROUNDCALCULATOR_H
