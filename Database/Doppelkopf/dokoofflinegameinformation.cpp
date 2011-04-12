#include "dokoofflinegameinformation.h"

START_ROW_IMPLEMENTATION(DokoOfflineGameInformation, OfflineGameInformation, OfflineGameInformation)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_hochzeiten,tr("Doko_Hochzeiten"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_soli,tr("Doko_Soli"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_trumpfabgaben,tr("Doko_Trumpfabgaben"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_rerounds,tr("Doko_ReRounds"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_rewins,tr("Doko_ReWins"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_contrarounds,tr("Doko_ContraRounds"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoOfflineGameInformation,doko_contrawins,tr("Doko_ContraWins"))
}

QString DokoOfflineGameInformation::mimeType() const
{
    return "application/projectstats.offlineGameInformation";
}

END_ROW_IMPLEMENTATION()
