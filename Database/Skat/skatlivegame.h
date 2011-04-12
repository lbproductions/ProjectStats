#ifndef DATABASE_SKATLIVEGAME_H
#define DATABASE_SKATLIVEGAME_H

#include "../livegame.h"

#include "../row.h"
#include "../table.h"
#include "../databaseattribute.h"

START_ROW_DECLARATION(SkatLiveGame, LiveGame)
    DECLARE_ROW_CONSTRUCTORS(SkatLiveGame, Game)

    DECLARE_DATABASEATTRIBUTE(bool,SkatLiveGame,skat_mitRamschen)
    DECLARE_DATABASEATTRIBUTE(QString,SkatLiveGame,skat_gameEnd)
    DECLARE_DATABASEATTRIBUTE(int,SkatLiveGame,skat_maxRounds)
    DECLARE_DATABASEATTRIBUTE(int,SkatLiveGame,skat_maxPoints)

END_ROW_DECLARATION(SkatLiveGame)

#endif // DATABASE_SKATLIVEGAME_H
