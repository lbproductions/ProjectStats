#ifndef DATABASE_ROUND_H
#define DATABASE_ROUND_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

START_ROW_DECLARATION(Round, Row)
    DECLARE_ROW_CONSTRUCTORS(Round, Round)

    DECLARE_DATABASEATTRIBUTE(int,Round,gameId)
    DECLARE_DATABASEATTRIBUTE(int,Round,number)
    DECLARE_DATABASEATTRIBUTE(QDateTime,Round,startTime)
    DECLARE_DATABASEATTRIBUTE(QTime,Round,length)
    DECLARE_DATABASEATTRIBUTE(int,Round,state)
    DECLARE_DATABASEATTRIBUTE(QString,Round,comment)

END_ROW_DECLARATION(Round)

START_TABLE_DECLARATION(Round)
END_TABLE_DECLARATION()

#endif // DATABASE_ROUND_H
