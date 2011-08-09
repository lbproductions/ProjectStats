#ifndef DATABASE_DOKOLIVEGAMECALCULATOR_H
#define DATABASE_DOKOLIVEGAMECALCULATOR_H

#include <Database/Calculator/livegamecalculator.h>

namespace Database {

class DokoLiveGame;
class Player;

class DokoLiveGameCalculator : public LiveGameCalculator
{
public:
    DokoLiveGameCalculator(DokoLiveGame* game);

    QMap<Player*,int> calculate_doko_re();

    QMap<Player*,int> calculate_doko_reWins();

    QMap<Player*,int> calculate_doko_contra();

    QMap<Player*,int> calculate_doko_contraWins();

    QMap<Player*,int> calculate_doko_hochzeit();

    QMap<Player*,int> calculate_doko_solo();

    QMap<Player*,int> calculate_doko_trumpfabgabe();

    QMap<Player*,int> calculate_doko_schweinerei();

    QMap<Player*,int> calculate_doko_schmeisserei();

    QMap<Player*,bool> calculate_doko_hasPflichtSolo();

    QMap<int,int> calculate_doko_hochzeitCountAfterRounds();

    QMap<int,int> calculate_doko_soloCountAfterRounds();

    QMap<int,int> calculate_doko_pflichtSoloCountAfterRounds();

    QMap<int,int> calculate_doko_trumpfabgabeCountAfterRounds();

    QMap<int,int> calculate_doko_schweinereiCountAfterRounds();

    QMap<int,int> calculate_doko_schmeissereiCountAfterRounds();

    QMap<QPair<Player*,Player*>,int> calculate_doko_gamesTogether();

    QMap<QPair<Player*,Player*>,int> calculate_doko_winsTogether();

    QMap<Player*,double> calculate_doko_pointAveragePerWin();

    QMap<Player*,int> calculate_doko_rounds();

    QMap<Player*,int> calculate_doko_roundWins();

    QMap<int,QMap<Player*,int> > calculate_placementAfterRounds();

    int calculate_doko_hochzeitCount();

    int calculate_doko_soloCount();

    int calculate_doko_pflichtSoloCount();

    int calculate_doko_trumpfabgabeCount();

    int calculate_doko_schweinereiCount();

    int calculate_doko_schmeissereiCount();

    int calculate_totalPoints();

private:
    QPointer<DokoLiveGame> m_dokolivegame;
};

} // namespace Database

#endif // DATABASE_DOKOLIVEGAMECALCULATOR_H
