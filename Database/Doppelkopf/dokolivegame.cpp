#include "dokolivegame.h"


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

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_re,"Doko_Re")
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_reWins,"Doko_Re_Wins")
}

QString DokoLiveGame::mimeType() const
{
    return "application/projectstats.dokoLiveGame";
}

END_ROW_IMPLEMENTATION()
