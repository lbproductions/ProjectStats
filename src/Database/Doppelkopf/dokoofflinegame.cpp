#include "dokoofflinegame.h"

START_ROW_IMPLEMENTATION(DokoOfflineGame, Game, OfflineGame)
{
}

QString DokoOfflineGame::mimeType() const
{
    return "application/projectstats.dokoOfflineGame";
}

END_ROW_IMPLEMENTATION()
