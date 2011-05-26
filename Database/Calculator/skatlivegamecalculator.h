#ifndef DATABASE_SKATLIVEGAMECALCULATOR_H
#define DATABASE_SKATLIVEGAMECALCULATOR_H

#include <Database/Calculator/livegamecalculator.h>

namespace Database {

class SkatLiveGame;

class SkatLiveGameCalculator : public LiveGameCalculator
{
public:
    SkatLiveGameCalculator(SkatLiveGame* game);

    AttributeHash<Player*,int> calculate_placement();

private:
    QPointer<SkatLiveGame> m_skatlivegame;
};

} // namespace Database

#endif // DATABASE_SKATLIVEGAMECALCULATOR_H
