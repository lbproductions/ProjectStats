#include "livegamedrink.h"

#include "player.h"
#include "round.h"
#include "drink.h"

#include <QDateTime>

START_TABLE_IMPLEMENTATION(LiveGameDrink)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(LiveGameDrink, LiveGameDrink, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,LiveGameDrink,playerId,tr("PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,LiveGameDrink,roundId,tr("RoundId"))
    IMPLEMENT_DATABASEATTRIBUTE(QDateTime,LiveGameDrink,time,tr("Time"))
    IMPLEMENT_DATABASEATTRIBUTE(int,LiveGameDrink,drinkId,tr("DrinkId"))

    IMPLEMENT_ATTRIBUTE(Drink*, LiveGameDrink, drink, tr("Drink"))
    drinkId->addDependingAttribute(drink);
}

LiveGameDrink::LiveGameDrink(Player* player, Round* round, Drink* drink) :
    Row(0,LiveGameDrinks::instance())
{
    initializeAttributes();

    this->playerId->setValue(player->id());
    this->roundId->setValue(round->id());
    this->drinkId->setValue(drink->id());
    this->time->setValue(QDateTime::currentDateTime());

    connect(player,SIGNAL(idChanged(int)),playerId,SLOT(changeValue(int)));
    connect(round,SIGNAL(idChanged(int)),roundId,SLOT(changeValue(int)));
    connect(drink,SIGNAL(idChanged(int)),drinkId,SLOT(changeValue(int)));
}

QString LiveGameDrink::mimeType() const
{
    return "application/projectstats.liveGameDrink";
}

Drink* LiveGameDrink::calculate_drink()
{
    return Drinks::instance()->rowById(drinkId->value());
}

END_ROW_IMPLEMENTATION()
