#include "round.h"

#include <Database/Doppelkopf/dokoround.h>
#include <Database/Skat/skatround.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include "game.h"
#include "point.h"

#include <QDateTime>
#include <QDebug>
#include <QTimer>

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

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Point*,Round,RoundCalculator,m_calc,pointInstances,tr("Point Instances"))

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Round,RoundCalculator,m_calc,points,tr("Points"))

    IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(int,Round,RoundCalculator,cardmixerPosition,tr("Cardmixer Position"))

    IMPLEMENT_VIRTUAL_LISTATTRIBUTE_IN_CALC(Player*,Round,RoundCalculator,currentPlayingPlayers, tr("CurrentPlayingPlayers"))

    IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(int,Round,RoundCalculator,roundPoints,tr("RoundPoints"))

    if(this->state->value() == Round::PausedState && !game->value().isNull())
    {
        length->addDependingAttribute(game->value()->length);
    }

    m_timer = 0;
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

void Round::addPoints(Player* player, int points)
{
    Point* point = new Point(this,player,points);
    addChildRow(point);

    this->pointInstances->recalculateFromScratch();
    this->points->recalculateFromScratch();
}

void Round::setState(RoundState state)
{
    if(state == this->state->value())
    {
        return;
    }

    if(!m_timer)
    {
        m_timer = new QTimer(this);
        connect(m_timer,SIGNAL(timeout()),this,SLOT(updateLength()));
    }

    switch(state)
    {
    case RunningState:
        m_timer->start(1000);
        break;
    case PausedState:
    case FinishedState:
        m_timer->stop();
        length->setValue(length->value());
        break;
    case UnkownState:
    default:
        break;
    }

    db_state->setValue(state);
}

void Round::updateLength()
{
    QTime time = length->value();
    if(time.isNull())
    {
        time = QTime(0,0);
    }
    time = time.addSecs(1);
    length->setValue(time, false);
}

END_ROW_IMPLEMENTATION()
