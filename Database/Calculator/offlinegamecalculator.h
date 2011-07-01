#ifndef OFFLINEGAMECALCULATOR_H
#define OFFLINEGAMECALCULATOR_H

#include <Database/attributehash.h>

#include <Database/Calculator/gamecalculator.h>

namespace Database{

class OfflineGame;
class Player;

class OfflineGameCalculator : public GameCalculator
{
public:
    OfflineGameCalculator(OfflineGame* game);

    AttributeHash<Player*,int> calculate_placement();

    AttributeHash<Player*,int> calculate_points();

    QTime calculate_length();

private:
    QPointer<OfflineGame> m_offlinegame;
};

}

#endif // OFFLINEGAMECALCULATOR_H