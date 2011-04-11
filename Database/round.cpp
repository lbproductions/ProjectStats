#include "round.h"

#include <QDateTime>

START_TABLE_IMPLEMENTATION(Round)
END_ROW_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Round, Round, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,Round,gameId,"Game")
    IMPLEMENT_DATABASEATTRIBUTE(int,Round,number,"Number")
    IMPLEMENT_DATABASEATTRIBUTE(QDateTime,Round,startTime,"Start-Time")
    IMPLEMENT_DATABASEATTRIBUTE(QTime,Round,length,"Length")
    IMPLEMENT_DATABASEATTRIBUTE(int,Round,state,"State")
    IMPLEMENT_DATABASEATTRIBUTE(QString,Round,comment,"Comment")
}

QString Round::mimeType() const
{
    return "application/projectstats.round";
}

END_ROW_IMPLEMENTATION()
