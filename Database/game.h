#ifndef DATABASE_GAME_H
#define DATABASE_GAME_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

START_ROW_DECLARATION(Game, Row)
    DECLARE_ROW_CONSTRUCTORS(Game, Game)

    DECLARE_DATABASEATTRIBUTE(QString,Game,name)
    DECLARE_DATABASEATTRIBUTE(QString,Game,type)
    DECLARE_DATABASEATTRIBUTE(bool,Game,live)
    DECLARE_DATABASEATTRIBUTE(QDateTime,Game,date)
    DECLARE_DATABASEATTRIBUTE(QTime,Game,length)
    DECLARE_DATABASEATTRIBUTE(QString,Game,comment)
    DECLARE_DATABASEATTRIBUTE(int,Game,siteId)


END_ROW_DECLARATION(Game)

START_TABLE_DECLARATION(Game)
END_TABLE_DECLARATION()

#endif // DATABASE_GAME_H
