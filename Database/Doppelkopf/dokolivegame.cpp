#include "dokolivegame.h"

START_ROW_IMPLEMENTATION(DokoLiveGame, Game, LiveGame)
{
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,mitHochzeit,tr("Mit Hochzeit"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,mitSolo,tr("Mit Solo"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,mitTrumpfabgabe,tr("Mit Trumpfabgabe"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,mitSchweinerei,tr("Mit Schweinerei"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,mitSchmeisserei,tr("Mit Schmeisserei"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,mitPflichtsolo,tr("Mit Pflichtsolo"))
}

QString DokoLiveGame::mimeType() const
{
    return "application/projectstats.dokoLiveGame";
}

END_ROW_IMPLEMENTATION()
