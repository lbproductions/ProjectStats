#ifndef DATABASE_LIVEGAMEDRINK_H
#define DATABASE_LIVEGAMEDRINK_H

#include <LBDatabase/LBDatabase.h>

namespace Database {
    class Drink;
    class Player;
    class Round;
}

START_ROW_DECLARATION(LiveGameDrink, Row)
    DECLARE_ROW_CONSTRUCTORS(LiveGameDrink, LiveGameDrink)

    LiveGameDrink(Player* player, Round* round, Drink* drink);

    DECLARE_DATABASEATTRIBUTE(int,LiveGameDrink,playerId)
    DECLARE_DATABASEATTRIBUTE(int,LiveGameDrink,roundId)
    DECLARE_DATABASEATTRIBUTE(QDateTime,LiveGameDrink,time)
    DECLARE_DATABASEATTRIBUTE(int,LiveGameDrink,drinkId)

    DECLARE_ATTRIBUTE(Drink*, LiveGameDrink, drink)

END_ROW_DECLARATION(LiveGameDrink)

START_TABLE_DECLARATION(LiveGameDrink)
END_TABLE_DECLARATION()

Q_DECLARE_METATYPE(QMap<Database::Player* COMMA QList<Database::LiveGameDrink*> >)

#endif // DATABASE_LIVEGAMEDRINK_H
