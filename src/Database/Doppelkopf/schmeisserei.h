#ifndef DATABASE_SCHMEISSEREI_H
#define DATABASE_SCHMEISSEREI_H


#include "../row.h"
#include "../table.h"
#include "../attribute.h"
#include "../databaseattribute.h"

namespace Database{
    class Player;
}

START_ROW_DECLARATION(Schmeisserei, Row)
    DECLARE_ROW_CONSTRUCTORS(Schmeisserei, Schmeisserei)

    Schmeisserei(Player* player, Round* round, QString type);

    DECLARE_DATABASEATTRIBUTE(int,Schmeisserei,roundId)
    DECLARE_DATABASEATTRIBUTE(int,Schmeisserei,playerId)
    DECLARE_DATABASEATTRIBUTE(QString,Schmeisserei,type)

    DECLARE_ATTRIBUTE(Player*,Schmeisserei,player)

END_ROW_DECLARATION(Schmeisserei)

START_TABLE_DECLARATION(Schmeisserei)
END_TABLE_DECLARATION()

#endif // DATABASE_SCHMEISSEREI_H
