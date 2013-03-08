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

    QMap<Player*,int> calculate_doko_rePercentage();

    QMap<Player*,int> calculate_doko_reWins();

    QMap<Player*,int> calculate_doko_reWinsPercentage();

    QMap<Player*,int> calculate_doko_contra();

    QMap<Player*,int> calculate_doko_contraPercentage();

    QMap<Player*,int> calculate_doko_contraWins();

    QMap<Player*,int> calculate_doko_contraWinsPercentage();

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

    QMap<RowPair,int> calculate_doko_gamesTogether();

    QMap<QList<Player*>,int> calculate_doko_winsTogether();

    QMap<Player*,double> calculate_doko_pointAveragePerWin();

    QMap<Player*,int> calculate_doko_rounds();

    QMap<Player*,int> calculate_doko_roundWins();

    QMap<Player*,double> calculate_doko_roundWinsPercentage();

    QMap<int,QMap<Player*,int> > calculate_placementAfterRounds();

    int calculate_doko_hochzeitCount();

    int calculate_doko_soloCount();

    int calculate_doko_pflichtSoloCount();

    int calculate_doko_trumpfabgabeCount();

    int calculate_doko_schweinereiCount();

    int calculate_doko_schmeissereiCount();

    int calculate_totalPoints();

    int calculate_doko_reRoundWins();

    int calculate_doko_contraRoundWins();

    QString calculate_doko_hochzeitStats();
    QString calculate_doko_soloStats();
    QString calculate_doko_pflichtSoloStats();
    QString calculate_doko_trumpfabgabeStats();
    QString calculate_doko_schweinereiStats();
    QString calculate_doko_schmeissereiStats();
    QString calculate_doko_reVsContraStats();
    QString calculate_doko_contraVsContraStats();

    QMap<int,int> calculate_doko_hochzeitPositionAfterRounds();
    QMap<int,int> calculate_doko_soloPositionAfterRounds();
    QMap<int,int> calculate_doko_trumpfabgabePositionAfterRounds();
    QMap<int,int> calculate_doko_pflichtSoloPositionAfterRounds();
    QMap<int,int> calculate_doko_schmeissereiPositionAfterRounds();
    QMap<int,int> calculate_doko_schweinereiPositionAfterRounds();
private:
    QPointer<DokoLiveGame> m_dokolivegame;

    QList<RowPair> createPairs(QList<Player*> players);
};

} // namespace Database

#endif // DATABASE_DOKOLIVEGAMECALCULATOR_H
