#ifndef DATABASE_SCHMEISSEREI_H
#define DATABASE_SCHMEISSEREI_H


#include "../row.h"
#include "../table.h"
#include "../attribute.h"
#include "../databaseattribute.h"

START_ROW_DECLARATION(Schmeisserei, Row)
    DECLARE_ROW_CONSTRUCTORS(Schmeisserei, Schmeisserei)

    DECLARE_DATABASEATTRIBUTE(int,Schmeisserei,roundId)
    DECLARE_DATABASEATTRIBUTE(int,Schmeisserei,playerId)
    DECLARE_DATABASEATTRIBUTE(QString,Schmeisserei,type)

END_ROW_DECLARATION(Schmeisserei)

START_TABLE_DECLARATION(Schmeisserei)
END_TABLE_DECLARATION()

#endif // DATABASE_SCHMEISSEREI_H
