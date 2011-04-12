#ifndef DATABASE_DOKOOFFLINEGAMEINFORMATION_H
#define DATABASE_DOKOOFFLINEGAMEINFORMATION_H

#include "../offlinegameinformation.h"

#include "../row.h"
#include "../table.h"
#include "../databaseattribute.h"

START_ROW_DECLARATION(DokoOfflineGameInformation, OfflineGameInformation)
    DECLARE_ROW_CONSTRUCTORS(DokoOfflineGameInformation, OfflineGameInformation)

    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_hochzeiten)
    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_soli)
    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_trumpfabgaben)
    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_rerounds)
    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_rewins)
    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_contrarounds)
    DECLARE_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_contrawins)


END_ROW_DECLARATION(DokoOfflineGameInformation)

#endif // DATABASE_DOKOOFFLINEGAMEINFORMATION_H
