#include "dokolivegame.h"

START_ROW_IMPLEMENTATION(DokoLiveGame, Game, LiveGame)
{
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitHochzeit,tr("Doko_MitHochzeit"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSolo,tr("Doko_MitSolo"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitTrumpfabgabe,tr("Doko_MitTrumpfabgabe"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchweinerei,tr("Doko_MitSchweinerei"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchmeisserei,tr("Doko_MitSchmeisserei"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitPflichtsolo,tr("Doko_MitPflichtsolo"))
}

QString DokoLiveGame::mimeType() const
{
    return "application/projectstats.dokoLiveGame";
}

END_ROW_IMPLEMENTATION()
