#include "schmeisserei.h"

START_TABLE_IMPLEMENTATION(Schmeisserei)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Schmeisserei, Schmeisserei, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,Schmeisserei,roundId,tr("RoundId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Schmeisserei,playerId,tr("PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Schmeisserei,type,tr("Type"))
}

QString Schmeisserei::mimeType() const
{
    return "application/projectstats.schmeisserei";
}

END_ROW_IMPLEMENTATION()
