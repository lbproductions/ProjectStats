#include "schmeisserei.h"

#include <Database/player.h>

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

QString Schmeisserei::mimeType() const
{
    return "application/projectstats.schmeisserei";
}

Player* Schmeisserei::calculate_player(){
    return Players::instance()->rowById(playerId->value());
}

END_ROW_IMPLEMENTATION()
