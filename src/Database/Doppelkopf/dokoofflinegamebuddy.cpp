#include "dokoofflinegamebuddy.h"

START_TABLE_IMPLEMENTATION(DokoOfflineGameBuddy)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(DokoOfflineGameBuddy, DokoOfflineGameBuddy, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameBuddy,gameId,tr("GameId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameBuddy,player1Id,tr("Player1Id"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameBuddy,player2Id,tr("Player2Id"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameBuddy,rounds,tr("Rounds"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameBuddy,wins,tr("Wins"))
}

QString DokoOfflineGameBuddy::mimeType() const
{
    return "application/projectstats.dokoOfflineGameBuddy";
}

END_ROW_IMPLEMENTATION()
