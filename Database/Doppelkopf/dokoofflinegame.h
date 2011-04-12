#ifndef DATABASE_DOKOOFFLINEGAME_H
#define DATABASE_DOKOOFFLINEGAME_H

#include "../offlinegame.h"

#include "../row.h"
#include "../table.h"
#include "../databaseattribute.h"

START_ROW_DECLARATION(DokoOfflineGame, OfflineGame)
    DECLARE_ROW_CONSTRUCTORS(DokoOfflineGame, Game)

END_ROW_DECLARATION(DokoOfflineGame)

#endif // DATABASE_DOKOOFFLINEGAME_H
