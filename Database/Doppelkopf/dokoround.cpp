#include "dokoround.h"

START_ROW_IMPLEMENTATION(DokoRound, Round, Round)
{

    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_hochzeitPlayerId,tr("Doko_HochzeitPlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_trumpfabgabePlayerId,tr("Doko_TrumpfabgabePlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_soloPlayerId,tr("Doko_SoloPlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_schweinereiPlayerId,tr("Doko_SchweinereiPlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_re1PlayerId,tr("Doko_Re1PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_re2PlayerId,tr("Doko_Re2PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,DokoRound,doko_soloType,tr("Doko_SoloType"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoRound,doko_soloPflicht,tr("Doko_SoloPflicht"))
}

QString DokoRound::mimeType() const
{
    return "application/projectstats.dokoRound";
}

END_ROW_IMPLEMENTATION()
