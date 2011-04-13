#include "round.h"

#include <QDateTime>

START_TABLE_IMPLEMENTATION(Round)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Round, Round, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,Round,gameId,tr("GameId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Round,number,tr("Number"))
    IMPLEMENT_DATABASEATTRIBUTE(QDateTime,Round,startTime,tr("Start-Time"))
    IMPLEMENT_DATABASEATTRIBUTE(QTime,Round,length,tr("Length"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Round,state,tr("State"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Round,comment,tr("Comment"))

    IMPLEMENT_ATTRIBUTE(QPointer<Game>,Round,game,tr("Game"))
    gameId->addDependingAttribute(game);
}

QString Round::mimeType() const
{
    return "application/projectstats.round";
}

QPointer<Game> Round::calculate_game(){
    return Games::instance()->rowById(this->gameId->value());
}

END_ROW_IMPLEMENTATION()
