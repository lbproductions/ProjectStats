#include "dokolivegame.h"

#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamerowwindow.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamedetailswidget.h>
#include <Database/Doppelkopf/dokoround.h>

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

    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitFuenfKoenige,tr("doko_mitZuWenigTrumpf"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitZuWenigTrumpf,tr("doko_mitZuWenigTrumpf"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitNeunzigPunkte,tr("doko_mitNeunzigPunkte"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitTrumpfabgabeSchmeisserei,tr("doko_mitTrumpfabgabeSchmeisserei"))

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_re,"Doko_Re")
    rounds->addDependingAttribute(doko_re);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_reWins,"Doko_Re_Wins")
    doko_re->addDependingAttribute(doko_reWins);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_contra,"Doko_Contra")
    rounds->addDependingAttribute(doko_contra);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_contraWins,"Doko_Contra_Wins")
    doko_contra->addDependingAttribute(doko_contraWins);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_hochzeit,tr("Doko_Hochzeit"))
    rounds->addDependingAttribute(doko_hochzeit);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_solo,tr("Doko_Solo"))
    rounds->addDependingAttribute(doko_solo);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_trumpfabgabe,tr("Doko_Trumpfabgabe"))
    rounds->addDependingAttribute(doko_trumpfabgabe);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schweinerei,tr("Doko_Schweinerei"))
    rounds->addDependingAttribute(doko_schweinerei);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schmeisserei,tr("Doko_Schmeisserei"))
    rounds->addDependingAttribute(doko_schmeisserei);
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
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_soloCountAfterRounds,tr("Doko_SoloCountAfterRounds"))
    doko_soloCount->addDependingAttribute(doko_soloCountAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_pflichtSoloCountAfterRounds,tr("Doko_PflichtSoloCountAfterRounds"))
    doko_pflichtSoloCount->addDependingAttribute(doko_pflichtSoloCountAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_trumpfabgabeCountAfterRounds,tr("Doko_TrumpfabgabeCountAfterRounds"))
    doko_trumpfabgabeCount->addDependingAttribute(doko_trumpfabgabeCountAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schweinereiCountAfterRounds,tr("Doko_SchweinereiCountAfterRounds"))
    doko_schweinereiCount->addDependingAttribute(doko_schweinereiCountAfterRounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(int,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schmeissereiCountAfterRounds,tr("Doko_SchmeissereiCountAfterRounds"))
    doko_schmeissereiCount->addDependingAttribute(doko_schmeissereiCountAfterRounds);

    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_hochzeitStats,tr("doko_hochzeitStats"))
    doko_hochzeitCount->addDependingAttribute(doko_hochzeitStats);
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_soloStats,tr("doko_hochzeitStats"))
    doko_soloCount->addDependingAttribute(doko_soloStats);
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_pflichtSoloStats,tr("doko_hochzeitStats"))
    doko_pflichtSoloCount->addDependingAttribute(doko_pflichtSoloStats);
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_trumpfabgabeStats,tr("doko_hochzeitStats"))
    doko_trumpfabgabeCount->addDependingAttribute(doko_trumpfabgabeStats);
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schweinereiStats,tr("doko_hochzeitStats"))
    doko_schweinereiCount->addDependingAttribute(doko_schweinereiStats);
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schmeissereiStats,tr("doko_hochzeitStats"))
    doko_schmeissereiCount->addDependingAttribute(doko_schmeissereiStats);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QPair<Player* COMMA Player*>,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_gamesTogether,tr("Doko_GamesTogether"))
    rounds->addDependingAttribute(doko_gamesTogether);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QPair<Player* COMMA Player*>,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_winsTogether,tr("Doko_WinsTogether"))
    rounds->addDependingAttribute(doko_winsTogether);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,double,DokoLiveGame,DokoLiveGameCalculator,calc,doko_pointAveragePerWin,tr("Doko_PointAveragePerWin"))
    rounds->addDependingAttribute(doko_pointAveragePerWin);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_rounds,tr("Doko_Rounds"))
    rounds->addDependingAttribute(doko_rounds);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_roundWins,tr("Doko_RoundWins"))
    rounds->addDependingAttribute(doko_roundWins);

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

Round *DokoLiveGame::createRound()
{
    DokoRound* round = new DokoRound(this,rounds->value().count());
    addChildRow(round);

    return round;
}

END_ROW_IMPLEMENTATION()
