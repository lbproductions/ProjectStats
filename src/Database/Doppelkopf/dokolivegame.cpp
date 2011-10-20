#include "dokolivegame.h"

#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamerowwindow.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamedetailswidget.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamesummarywidget.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/Doppelkopf/schmeisserei.h>

const QString Database::DokoLiveGame::TYPE("Doppelkopf");

START_ROW_IMPLEMENTATION(DokoLiveGame, Game, LiveGame)
{
    DokoLiveGameCalculator* calc = new DokoLiveGameCalculator(this);
    m_calc = calc;

    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitHochzeit,tr("Doko_MitHochzeit"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSolo,tr("Doko_MitSolo"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitTrumpfabgabe,tr("Doko_MitTrumpfabgabe"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchweinerei,tr("Doko_MitSchweinerei"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchmeisserei,tr("Doko_MitSchmeisserei"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitPflichtsolo,tr("Doko_MitPflichtsolo"))

    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitBubensolo,tr("doko_mitBubensolo"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitDamensolo,tr("doko_mitDamensolo"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitFarbsolo,tr("doko_mitFarbsolo"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitFleischlos,tr("doko_mitFleischlos"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitTrumpfsolo,tr("doko_mitTrumpfsolo"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchwarzsolo,tr("doko_mitSchwarzsolo"))

    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitFuenfKoenige,tr("doko_mitZuWenigTrumpf"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitZuWenigTrumpf,tr("doko_mitZuWenigTrumpf"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitNeunzigPunkte,tr("doko_mitNeunzigPunkte"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitTrumpfabgabeSchmeisserei,tr("doko_mitTrumpfabgabeSchmeisserei"))

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_re,"Doko_Re")
    rounds->addDependingAttribute(doko_re);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_rePercentage,"Doko_RePercentage")
    doko_re->addDependingAttribute(doko_rePercentage);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_reWins,"Doko_Re_Wins")
    doko_re->addDependingAttribute(doko_reWins);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_reWinsPercentage,"Doko_ReWinsPercentage")
    doko_re->addDependingAttribute(doko_reWinsPercentage);
    doko_reWins->addDependingAttribute(doko_reWinsPercentage);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_contra,"Doko_Contra")
    rounds->addDependingAttribute(doko_contra);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_contraPercentage,"Doko_ContraPercentage")
    doko_contra->addDependingAttribute(doko_contraPercentage);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_contraWins,"Doko_Contra_Wins")
    doko_contra->addDependingAttribute(doko_contraWins);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_contraWinsPercentage,"Doko_ContraWinsPercentage")
    doko_contra->addDependingAttribute(doko_contraWinsPercentage);
    doko_contraWins->addDependingAttribute(doko_contraWinsPercentage);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_hochzeit,tr("Doko_Hochzeit"))
    rounds->addDependingAttribute(doko_hochzeit);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_solo,tr("Doko_Solo"))
    rounds->addDependingAttribute(doko_solo);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_trumpfabgabe,tr("Doko_Trumpfabgabe"))
    rounds->addDependingAttribute(doko_trumpfabgabe);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schweinerei,tr("Doko_Schweinerei"))
    rounds->addDependingAttribute(doko_schweinerei);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schmeisserei,tr("Doko_Schmeisserei"))
    Schmeissereis::instance()->rows()->addDependingAttribute(doko_schmeisserei);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,bool,DokoLiveGame,DokoLiveGameCalculator,calc,doko_hasPflichtSolo,tr("Doko_HasPflichtsolo"))
    rounds->addDependingAttribute(doko_hasPflichtSolo);

    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_hochzeitCount,tr("Doko_HochzeitCount"))
    doko_hochzeit->addDependingAttribute(doko_hochzeitCount);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_soloCount,tr("Doko_SoloCount"))
    doko_solo->addDependingAttribute(doko_soloCount);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_pflichtSoloCount,tr("Doko_PflichtSoloCount"))
    doko_hasPflichtSolo->addDependingAttribute(doko_pflichtSoloCount);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_trumpfabgabeCount,tr("Doko_TrumpfabgabenCount"))
    doko_trumpfabgabe->addDependingAttribute(doko_trumpfabgabeCount);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schweinereiCount,tr("Doko_SchweinereienCount"))
    doko_schweinerei->addDependingAttribute(doko_schweinereiCount);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schmeissereiCount,tr("Doko_SchmeissereienCount"))
    doko_schmeisserei->addDependingAttribute(doko_schmeissereiCount);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_hochzeitCountAfterRounds,tr("Doko_HochzeitCountAfterRounds"))
    doko_hochzeitCount->addDependingAttribute(doko_hochzeitCountAfterRounds);
    roundCount->addDependingAttribute(doko_hochzeitCountAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_soloCountAfterRounds,tr("Doko_SoloCountAfterRounds"))
    doko_soloCount->addDependingAttribute(doko_soloCountAfterRounds);
    roundCount->addDependingAttribute(doko_soloCountAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_pflichtSoloCountAfterRounds,tr("Doko_PflichtSoloCountAfterRounds"))
    doko_pflichtSoloCount->addDependingAttribute(doko_pflichtSoloCountAfterRounds);
    roundCount->addDependingAttribute(doko_pflichtSoloCountAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_trumpfabgabeCountAfterRounds,tr("Doko_TrumpfabgabeCountAfterRounds"))
    doko_trumpfabgabeCount->addDependingAttribute(doko_trumpfabgabeCountAfterRounds);
    roundCount->addDependingAttribute(doko_trumpfabgabeCountAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schweinereiCountAfterRounds,tr("Doko_SchweinereiCountAfterRounds"))
    doko_schweinereiCount->addDependingAttribute(doko_schweinereiCountAfterRounds);
    roundCount->addDependingAttribute(doko_schweinereiCountAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schmeissereiCountAfterRounds,tr("Doko_SchmeissereiCountAfterRounds"))
    doko_schmeissereiCount->addDependingAttribute(doko_schmeissereiCountAfterRounds);
    roundCount->addDependingAttribute(doko_schmeissereiCountAfterRounds);

    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_hochzeitStats,tr("Doko_HochzeitStats"))
    doko_hochzeitCountAfterRounds->addDependingAttribute(doko_hochzeitStats);
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_soloStats,tr("Doko_SoloStats"))
    doko_soloCountAfterRounds->addDependingAttribute(doko_soloStats);
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_pflichtSoloStats,tr("Doko_PflichtSoloStats"))
    doko_pflichtSoloCountAfterRounds->addDependingAttribute(doko_pflichtSoloStats);
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_trumpfabgabeStats,tr("Doko_TrumpfabgabeStats"))
    doko_trumpfabgabeCountAfterRounds->addDependingAttribute(doko_trumpfabgabeStats);
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schweinereiStats,tr("Doko_SchweinereiStats"))
    doko_schweinereiCountAfterRounds->addDependingAttribute(doko_schweinereiStats);
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schmeissereiStats,tr("Doko_SchmeissereiStats"))
    doko_schmeissereiCountAfterRounds->addDependingAttribute(doko_schmeissereiStats);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QPair<Player* COMMA Player*>,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_gamesTogether,tr("Doko_GamesTogether"))
    roundCount->addDependingAttribute(doko_gamesTogether);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QPair<Player* COMMA Player*>,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_winsTogether,tr("Doko_WinsTogether"))
    roundCount->addDependingAttribute(doko_winsTogether);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,double,DokoLiveGame,DokoLiveGameCalculator,calc,doko_pointAveragePerWin,tr("Doko_PointAveragePerWin"))
    rounds->addDependingAttribute(doko_pointAveragePerWin);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_rounds,tr("Doko_Rounds"))
    rounds->addDependingAttribute(doko_rounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_roundWins,tr("Doko_RoundWins"))
    rounds->addDependingAttribute(doko_roundWins);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,double,DokoLiveGame,DokoLiveGameCalculator,calc,doko_roundWinsPercentage,tr("RoundWinsPercentage"))
    rounds->addDependingAttribute(doko_roundWinsPercentage);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_reRoundWins,tr("ReRoundWins"))
    rounds->addDependingAttribute(doko_reRoundWins);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_contraRoundWins,tr("ContraRoundWins"))
    rounds->addDependingAttribute(doko_contraRoundWins);
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_reVsContraStats,tr("ReVsContraStats"))
    doko_reRoundWins->addDependingAttribute(doko_reVsContraStats);
    doko_contraRoundWins->addDependingAttribute(doko_reVsContraStats);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_hochzeitPositionAfterRounds,tr("Doko_HochzeitPositionAfterRounds"))
    doko_hochzeitCount->addDependingAttribute(doko_hochzeitPositionAfterRounds);
    roundCount->addDependingAttribute(doko_hochzeitPositionAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_soloPositionAfterRounds,tr("Doko_SoloPositionAfterRounds"))
    doko_soloCount->addDependingAttribute(doko_soloPositionAfterRounds);
    roundCount->addDependingAttribute(doko_soloPositionAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_pflichtSoloPositionAfterRounds,tr("Doko_PflichtSoloPositionAfterRounds"))
    doko_pflichtSoloCount->addDependingAttribute(doko_pflichtSoloPositionAfterRounds);
    roundCount->addDependingAttribute(doko_pflichtSoloPositionAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_trumpfabgabePositionAfterRounds,tr("Doko_TrumpfabgabePositionAfterRounds"))
    doko_trumpfabgabeCount->addDependingAttribute(doko_trumpfabgabePositionAfterRounds);
    roundCount->addDependingAttribute(doko_trumpfabgabePositionAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schweinereiPositionAfterRounds,tr("Doko_SchweinereiPositionAfterRounds"))
    doko_schweinereiCount->addDependingAttribute(doko_schweinereiPositionAfterRounds);
    roundCount->addDependingAttribute(doko_schweinereiPositionAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schmeissereiPositionAfterRounds,tr("Doko_SchmeissereiPositionAfterRounds"))
    doko_schmeissereiCountAfterRounds->addDependingAttribute(doko_schmeissereiPositionAfterRounds);
    roundCount->addDependingAttribute(doko_schmeissereiPositionAfterRounds);

}

DokoLiveGame::DokoLiveGame(bool mitHochzeit,
                            bool mitSolo,
                            bool mitTrumpfabgabe,
                            bool mitSchweinerei,
                            bool mitSchmeisserei,
                            bool mitPflichtsolo,
                            bool mitBubensolo,
                            bool mitDamensolo,
                            bool mitFarbsolo,
                            bool mitFleischlos,
                            bool mitTrumpfsolo,
                            bool mitSchwarzsolo,
                            bool mitFuenfKoenige,
                            bool mitZuWenigTrumpf,
                            bool mitNeunzigPunkte,
                            bool mitTrumpfabgabeSchmeisserei) :
    LiveGame(TYPE)
{
    initializeAttributes();

    doko_mitHochzeit->setValue(mitHochzeit);
    doko_mitSolo->setValue(mitSolo);
    doko_mitTrumpfabgabe->setValue(mitTrumpfabgabe);
    doko_mitSchweinerei->setValue(mitSchweinerei);
    doko_mitSchmeisserei->setValue(mitSchmeisserei);
    doko_mitPflichtsolo->setValue(mitPflichtsolo);

    doko_mitBubensolo->setValue(mitBubensolo);
    doko_mitDamensolo->setValue(mitDamensolo);
    doko_mitFarbsolo->setValue(mitFarbsolo);
    doko_mitFleischlos->setValue(mitFleischlos);
    doko_mitTrumpfsolo->setValue(mitTrumpfsolo);
    doko_mitSchwarzsolo->setValue(mitSchwarzsolo);

    doko_mitFuenfKoenige->setValue(mitFuenfKoenige);
    doko_mitZuWenigTrumpf->setValue(mitZuWenigTrumpf);
    doko_mitNeunzigPunkte->setValue(mitNeunzigPunkte);
    doko_mitTrumpfabgabeSchmeisserei->setValue(mitTrumpfabgabeSchmeisserei);
}

QString DokoLiveGame::mimeType() const
{
    return "application/projectstats.dokoLiveGame";
}

Gui::Details::DetailsWidget* DokoLiveGame::detailsWidget()
{
    return new Gui::Details::DokoLiveGameDetailsWidget(this);
}

Gui::Details::RowWindow* DokoLiveGame::rowWindow()
{
    return new Gui::Details::DokoLiveGameRowWindow(this);
}

Gui::Details::SummaryWidget* DokoLiveGame::summaryWidget(){
    return new Gui::Details::LiveGameDetails::DokoLiveGameDetails::DokoLiveGameSummaryWidget(this);
}

Round *DokoLiveGame::createRound()
{
    DokoRound* round = new DokoRound(this,rounds->value().count());
    addChildRow(round);

    return round;
}

END_ROW_IMPLEMENTATION()
