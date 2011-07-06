#include "position.h"

#include "player.h"
#include "game.h"

START_TABLE_IMPLEMENTATION(Position)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Position, Position, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,Position,playerId,tr("PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Position,gameId,tr("GameId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Position,position,tr("Position"))
}

Position::Position(Player* player, Game* game, int position) :
    Row(0,Positions::instance())
{
    initializeAttributes();

    this->playerId->setValue(player->id());
    this->gameId->setValue(game->id());
    this->position->setValue(position);

    connect(game,SIGNAL(idChanged(int)),this->gameId,SLOT(setValue(int)));
    connect(player,SIGNAL(idChanged(int)),this->playerId,SLOT(setValue(int)));
}

QString Position::mimeType() const
{
    return "application/projectstats.position";
}

END_ROW_IMPLEMENTATION()
