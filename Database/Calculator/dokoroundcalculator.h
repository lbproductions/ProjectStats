#ifndef DATABASE_DOKOROUNDCALCULATOR_H
#define DATABASE_DOKOROUNDCALCULATOR_H

#include <Database/Calculator/roundcalculator.h>
#include <Database/attributelist.h>

namespace Database {

class DokoRound;
class Player;
class Schmeisserei;

class DokoRoundCalculator : public RoundCalculator
{
public:
    DokoRoundCalculator(DokoRound* round);

    AttributeList<Player*> calculate_currentPlayingPlayers();

    int calculate_roundPoints();

    AttributeList<Schmeisserei*> calculate_doko_schmeissereien();

    AttributeHash<Player*,bool> calculate_doko_re();

private:
    QPointer<DokoRound> m_dokoround;
};

} // namespace Database

#endif // DATABASE_DOKOROUNDCALCULATOR_H
