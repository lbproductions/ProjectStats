#include "skatlivegame.h"

START_ROW_IMPLEMENTATION(SkatLiveGame, Game, LiveGame)
{
    IMPLEMENT_DATABASEATTRIBUTE(bool,SkatLiveGame,skat_mitRamschen,tr("Skat_MitRamschen"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,SkatLiveGame,skat_gameEnd,tr("Skat_GameEnd"))
    IMPLEMENT_DATABASEATTRIBUTE(int,SkatLiveGame,skat_maxRounds,tr("Skat_MaxRounds"))
    IMPLEMENT_DATABASEATTRIBUTE(int,SkatLiveGame,skat_maxPoints,tr("Skat_MaxPoints"))
}

QString SkatLiveGame::mimeType() const
{
    return "application/projectstats.skatLiveGame";
}

END_ROW_IMPLEMENTATION()

