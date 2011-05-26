#include "round.h"

#include <QDateTime>

START_TABLE_IMPLEMENTATION(Round)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Round, Round, Row)
{
    m_calc = new RoundCalculator(this);

    IMPLEMENT_DATABASEATTRIBUTE(int,Round,gameId,tr("GameId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Round,number,tr("Number"))
    IMPLEMENT_DATABASEATTRIBUTE(QDateTime,Round,startTime,tr("Start-Time"))
    IMPLEMENT_DATABASEATTRIBUTE(QTime,Round,length,tr("Length"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Round,db_state,tr("DB-State"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Round,comment,tr("Comment"))

    IMPLEMENT_ATTRIBUTE(QPointer<Game>,Round,game,tr("Game"))
    gameId->addDependingAttribute(game);
    IMPLEMENT_ATTRIBUTE(RoundState,Round,state,tr("State"))
    db_state->addDependingAttribute(state);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Round,RoundCalculator,m_calc,points,tr("Points"))

    IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(int,Round,RoundCalculator,cardmixerPosition,tr("Cardmixer Position"))

    IMPLEMENT_VIRTUAL_LISTATTRIBUTE_IN_CALC(Player*,Round,RoundCalculator,currentPlayingPlayers, tr("CurrentPlayingPlayers"))

    IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(int,Round,RoundCalculator,roundPoints,tr("RoundPoints"))
}

QString Round::mimeType() const
{
    return "application/projectstats.round";
}

QPointer<Game> Round::calculate_game(){
    return Games::instance()->rowById(this->gameId->value());
}

Round::RoundState Round::calculate_state(){
    return (RoundState)this->db_state->value();
}

END_ROW_IMPLEMENTATION()
