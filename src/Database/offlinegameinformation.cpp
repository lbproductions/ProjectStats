#include "offlinegameinformation.h"

START_TABLE_IMPLEMENTATION(OfflineGameInformation)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(OfflineGameInformation, OfflineGameInformation, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,OfflineGameInformation,gameId,tr("GameId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,OfflineGameInformation,playerId,tr("PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,OfflineGameInformation,placement,tr("Placement"))
    IMPLEMENT_DATABASEATTRIBUTE(int,OfflineGameInformation,points,tr("Points"))
}

QString OfflineGameInformation::mimeType() const
{
    return "application/projectstats.offlineGameInformation";
}

END_ROW_IMPLEMENTATION()
