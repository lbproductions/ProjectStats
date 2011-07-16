#include "round.h"

#include <Database/Doppelkopf/dokoround.h>
#include <Database/Skat/skatround.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include "game.h"

#include <QDateTime>
#include <QDebug>

START_TABLE_IMPLEMENTATION(Round)

QPointer<Round> Rounds::createRowInstance(int id)
{
    Round *row = new Round(id,this);
    Round *row2 = 0;

    if(row->game->value()->type->value() == DokoLiveGame::TYPE)
    {
        row2 = new DokoRound(id,this);
    }
    else if(row->game->value()->type->value() == "Skat")
    {
        row2 = new SkatRound(id,this);
    }


    if(row2 != 0)
    {
        return row2;
    }

    return row;
}

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
    state->setRole(Qt::DecorationRole);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Round,RoundCalculator,m_calc,points,tr("Points"))

    IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(int,Round,RoundCalculator,cardmixerPosition,tr("Cardmixer Position"))

    IMPLEMENT_VIRTUAL_LISTATTRIBUTE_IN_CALC(Player*,Round,RoundCalculator,currentPlayingPlayers, tr("CurrentPlayingPlayers"))

    IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(int,Round,RoundCalculator,roundPoints,tr("RoundPoints"))
}

Round::Round(Game* game, int number) :
    Row(0,Rounds::instance())
{
    initializeAttributes();
    this->gameId->setValue(game->id());
    this->number->setValue(number);

    this->startTime->setValue(QDateTime::currentDateTime());
    this->db_state->setValue(Round::RunningState);

    connect(game,SIGNAL(idChanged(int)),gameId,SLOT(changeValue(int)));
}

QString Round::mimeType() const
{
    return "application/projectstats.round";
}

QPointer<Game> Round::calculate_game()
{
    Game *game = Games::instance()->rowById(this->gameId->value());
    state->addDependingAttribute(game->state);
    return game;
}

Round::RoundState Round::calculate_state()
{
    return (RoundState)db_state->value();
}

END_ROW_IMPLEMENTATION()
