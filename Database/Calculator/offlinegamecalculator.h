#ifndef OFFLINEGAMECALCULATOR_H
#define OFFLINEGAMECALCULATOR_H

#include <Database/Calculator/gamecalculator.h>

namespace Database{

class OfflineGame;
class Player;

class OfflineGameCalculator : public GameCalculator
{
public:
    OfflineGameCalculator(OfflineGame* game);

    QMap<Player*,int> calculate_placement();

    QMap<Player*,int> calculate_points();

    QTime calculate_length();

private:
    QPointer<OfflineGame> m_offlinegame;
};

}

#endif // OFFLINEGAMECALCULATOR_H
