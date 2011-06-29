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

    AttributeHash<Player*,int> calculate_doko_contra();

    AttributeHash<Player*,int> calculate_doko_contraWins();

    AttributeHash<Player*,int> calculate_doko_hochzeit();

    AttributeHash<Player*,int> calculate_doko_solo();

    AttributeHash<Player*,int> calculate_doko_trumpfabgabe();

    AttributeHash<Player*,int> calculate_doko_schweinerei();

    AttributeHash<Player*,int> calculate_doko_schmeisserei();

    AttributeHash<Player*,bool> calculate_doko_hasPflichtSolo();

    AttributeHash<int,int> calculate_doko_hochzeitCountAfterRounds();

    AttributeHash<int,int> calculate_doko_soloCountAfterRounds();

    AttributeHash<int,int> calculate_doko_pflichtSoloCountAfterRounds();

    AttributeHash<int,int> calculate_doko_trumpfabgabeCountAfterRounds();

    AttributeHash<int,int> calculate_doko_schweinereiCountAfterRounds();

    AttributeHash<int,int> calculate_doko_schmeissereiCountAfterRounds();

    AttributeHash<QPair<Player*,Player*>,int> calculate_doko_gamesTogether();

    AttributeHash<QPair<Player*,Player*>,int> calculate_doko_winsTogether();

    AttributeHash<Player*,double> calculate_doko_pointAveragePerWin();

    AttributeHash<Player*,int> calculate_doko_rounds();

    AttributeHash<Player*,int> calculate_doko_roundWins();

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
