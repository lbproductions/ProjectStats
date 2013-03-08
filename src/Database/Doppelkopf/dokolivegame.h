#ifndef DATABASE_DOKOLIVEGAME_H
#define DATABASE_DOKOLIVEGAME_H

#include "../livegame.h"

#include "../row.h"
#include "../table.h"
#include "../databaseattribute.h"
#include "../rowpair.h"

#include <QPair>

#include <Database/mappingattribute.h>
#include <Database/Calculator/dokolivegamecalculator.h>

namespace Database
{
    class DokoRound;
}

START_ROW_DECLARATION(DokoLiveGame, LiveGame)
    DECLARE_ROW_CONSTRUCTORS(DokoLiveGame, Game)

    DokoLiveGame(bool mitHochzeit,
                 bool mitSolo,
                 bool mitTrumpfabgabe,
                 bool mitSchweinerei,
                 bool mitSchmeisserei,
                 bool mitPflichtsolo,
                 bool mitBubensolo,
                 bool mitDamensolo,
                 bool mitFarbsolo,
                 bool mitFleischloss,
                 bool mitTrumpfsolo,
                 bool mitSchwarzsolo,
                 bool mitFuenfKoenige,
                 bool mitZuWenigTrumpf,
                 bool mitNeunzigPunkte,
                 bool mitTrumpfabgabeSchmeisserei);

    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitHochzeit)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSolo)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitTrumpfabgabe)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchweinerei)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchmeisserei)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitPflichtsolo)

    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitBubensolo)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitDamensolo)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitFarbsolo)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitFleischlos)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitTrumpfsolo)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchwarzsolo)

    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitFuenfKoenige)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitZuWenigTrumpf)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitNeunzigPunkte)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitTrumpfabgabeSchmeisserei)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_re)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_rePercentage)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_reWins)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_reWinsPercentage)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_contra)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_contraPercentage)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_contraWins)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_contraWinsPercentage)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_hochzeit)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_solo)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_trumpfabgabe)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_schweinerei)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_schmeisserei)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,bool,DokoLiveGame,DokoLiveGameCalculator,doko_hasPflichtSolo)

    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_hochzeitCount)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_soloCount)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_pflichtSoloCount)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_trumpfabgabeCount)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_schweinereiCount)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_schmeissereiCount)


    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_hochzeitCountAfterRounds)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_soloCountAfterRounds)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_pflichtSoloCountAfterRounds)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_trumpfabgabeCountAfterRounds)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_schweinereiCountAfterRounds)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_schmeissereiCountAfterRounds)

    DECLARE_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,doko_reVsContraStats)
    DECLARE_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,doko_hochzeitStats)
    DECLARE_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,doko_soloStats)
    DECLARE_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,doko_pflichtSoloStats)
    DECLARE_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,doko_trumpfabgabeStats)
    DECLARE_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,doko_schweinereiStats)
    DECLARE_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,doko_schmeissereiStats)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(RowPair ,int,DokoLiveGame,DokoLiveGameCalculator,doko_gamesTogether)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QList<Player*> ,int,DokoLiveGame,DokoLiveGameCalculator,doko_winsTogether)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,double,DokoLiveGame,DokoLiveGameCalculator,doko_pointAveragePerWin)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_rounds)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_roundWins)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,double,DokoLiveGame,DokoLiveGameCalculator,doko_roundWinsPercentage)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_reRoundWins)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_contraRoundWins)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_hochzeitPositionAfterRounds)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_soloPositionAfterRounds)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_pflichtSoloPositionAfterRounds)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_trumpfabgabePositionAfterRounds)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_schweinereiPositionAfterRounds)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,doko_schmeissereiPositionAfterRounds)

    virtual Gui::Details::DetailsWidget* detailsWidget();

    virtual Gui::Details::RowWindow* rowWindow();

    Gui::Details::SummaryWidget* summaryWidget();

    static const QString TYPE;

protected:
    Round *createRound();

END_ROW_DECLARATION(DokoLiveGame)

#endif // DATABASE_DOPPELKOPF_DOKOLIVEGAME_H
