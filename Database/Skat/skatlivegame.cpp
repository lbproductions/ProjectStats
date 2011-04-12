#include "skatlivegame.h"

START_ROW_IMPLEMENTATION(SkatLiveGame, Game, LiveGame)
{
    IMPLEMENT_DATABASEATTRIBUTE(bool,SkatLiveGame,skat_mitRamschen,"Skat_MitRamschen")
    IMPLEMENT_DATABASEATTRIBUTE(QString,SkatLiveGame,skat_gameEnd,"Skat_GameEnd")
    IMPLEMENT_DATABASEATTRIBUTE(int,SkatLiveGame,skat_maxRounds,"Skat_MaxRounds")
    IMPLEMENT_DATABASEATTRIBUTE(int,SkatLiveGame,skat_maxPoints,"Skat_MaxPoints")
}

QString SkatLiveGame::mimeType() const
{
    return "application/projectstats.skatLiveGame";
}

END_ROW_IMPLEMENTATION()

