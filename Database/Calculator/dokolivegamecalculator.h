#ifndef DATABASE_DOKOLIVEGAMECALCULATOR_H
#define DATABASE_DOKOLIVEGAMECALCULATOR_H

#include <Database/Calculator/livegamecalculator.h>
#include <Database/attributehash.h>

namespace Database {

class DokoLiveGame;
class Player;

class DokoLiveGameCalculator : public LiveGameCalculator
{
public:
    DokoLiveGameCalculator(DokoLiveGame* game);

    AttributeHash<Player*,int> calculate_doko_re();

    AttributeHash<Player*,int> calculate_doko_reWins();

    int calculate_totalPoints();

private:
    QPointer<DokoLiveGame> m_dokolivegame;
};

} // namespace Database

#endif // DATABASE_DOKOLIVEGAMECALCULATOR_H
