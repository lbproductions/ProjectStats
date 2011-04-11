#include "offlinegame.h"

START_ROW_IMPLEMENTATION(OfflineGame, Game, Game)
{
}

QString OfflineGame::mimeType() const
{
    return "application/projectstats.offlineGame";
}

END_ROW_IMPLEMENTATION()
