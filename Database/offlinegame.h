#ifndef DATABASE_OFFLINEGAME_H
#define DATABASE_OFFLINEGAME_H

#include "game.h"

#include "row.h"
#include "table.h"
#include "databaseattribute.h"

#include <Database/Calculator/offlinegamecalculator.h>

START_ROW_DECLARATION(OfflineGame, Game)
    DECLARE_ROW_CONSTRUCTORS(OfflineGame, Game)

END_ROW_DECLARATION(OfflineGame)

#endif // DATABASE_OFFLINEGAME_H
