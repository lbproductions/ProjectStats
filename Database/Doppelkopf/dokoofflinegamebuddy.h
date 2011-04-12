#ifndef DATABASE_DOKOOFFLINEGAMEBUDDY_H
#define DATABASE_DOKOOFFLINEGAMEBUDDY_H

#include "../row.h"
#include "../table.h"
#include "../attribute.h"
#include "../databaseattribute.h"

START_ROW_DECLARATION(DokoOfflineGameBuddy, Row)
    DECLARE_ROW_CONSTRUCTORS(DokoOfflineGameBuddy, DokoOfflineGameBuddy)

    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameBuddy,gameId)
    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameBuddy,player1Id)
    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameBuddy,player2Id)
    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameBuddy,rounds)
    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameBuddy,wins)


END_ROW_DECLARATION(DokoOfflineGameBuddy)

START_TABLE_DECLARATION(DokoOfflineGameBuddy)
END_TABLE_DECLARATION()

#endif // DATABASE_DOKOOFFLINEBUDDY_H
