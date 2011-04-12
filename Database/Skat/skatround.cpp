#include "skatround.h"

START_ROW_IMPLEMENTATION(SkatRound, Round, Round)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,SkatRound,skat_solistPlayerId,tr("Skat_SolistPlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,SkatRound,skat_gameType,tr("Skat_GameType"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,SkatRound,skat_trumpfColor,tr("Skat_TrumpfColor"))
}

QString SkatRound::mimeType() const
{
    return "application/projectstats.skatRound";
}

END_ROW_IMPLEMENTATION()
