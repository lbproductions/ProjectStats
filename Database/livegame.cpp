#include "livegame.h"

START_ROW_IMPLEMENTATION(LiveGame, Game, Game)
{
}

QString LiveGame::mimeType() const
{
    return "application/projectstats.liveGame";
}

END_ROW_IMPLEMENTATION()
