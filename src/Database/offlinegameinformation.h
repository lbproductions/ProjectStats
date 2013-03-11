#ifndef DATABASE_OFFLINEGAMEINFORMATION_H
#define DATABASE_OFFLINEGAMEINFORMATION_H

#include "row.h"
#include "table.h"
#include "databaseattribute.h"

START_ROW_DECLARATION(OfflineGameInformation, Row)
#if QT_VERSION > 0x050000
    Q_OBJECT
#endif

    DECLARE_ROW_CONSTRUCTORS(OfflineGameInformation, OfflineGameInformation)

    DECLARE_DATABASEATTRIBUTE(int,OfflineGameInformation,gameId)
    DECLARE_DATABASEATTRIBUTE(int,OfflineGameInformation,playerId)
    DECLARE_DATABASEATTRIBUTE(int,OfflineGameInformation,placement)
    DECLARE_DATABASEATTRIBUTE(int,OfflineGameInformation,points)

END_ROW_DECLARATION(OfflineGameInformation)

START_TABLE_DECLARATION(OfflineGameInformation)
END_TABLE_DECLARATION()

#endif // DATABASE_OFFLINEGAMEINFORMATION_H
