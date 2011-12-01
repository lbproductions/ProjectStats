#include "schmeisserei.h"

#include <Database/player.h>
#include <Database/round.h>

START_TABLE_IMPLEMENTATION(Schmeisserei)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Schmeisserei, Schmeisserei, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,Schmeisserei,roundId,tr("RoundId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Schmeisserei,playerId,tr("PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Schmeisserei,type,tr("Type"))

    IMPLEMENT_ATTRIBUTE(Player*,Schmeisserei,player,tr("Player"))
    playerId->addDependingAttribute(player);
}

Schmeisserei::Schmeisserei(Player* player, Round* round, QString type) :
    Row(0,Schmeissereis::instance())
{
    initializeAttributes();

    this->playerId->setValue(player->id());
    this->roundId->setValue(round->id());
    this->type->setValue(type);

    connect(player,SIGNAL(idChanged(int)),playerId,SLOT(setValue(int)));
    connect(round,SIGNAL(idChanged(int)),roundId,SLOT(setValue(int)));
}

QString Schmeisserei::mimeType() const
{
    return "application/projectstats.schmeisserei";
}

Player* Schmeisserei::calculate_player(){
    return Players::instance()->castedRowById(playerId->value());
}

END_ROW_IMPLEMENTATION()
