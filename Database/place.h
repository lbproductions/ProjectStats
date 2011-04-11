#ifndef DATABASE_PLACE_H
#define DATABASE_PLACE_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

START_ROW_DECLARATION(Place, Row)
    DECLARE_ROW_CONSTRUCTORS(Place, Place)

    DECLARE_DATABASEATTRIBUTE(int,Place,playerId)
    DECLARE_DATABASEATTRIBUTE(int,Place,plz)
    DECLARE_DATABASEATTRIBUTE(QString,Place,ort)
    DECLARE_DATABASEATTRIBUTE(QString,Place,strasse)
    DECLARE_DATABASEATTRIBUTE(int,Place,nummer)
    DECLARE_DATABASEATTRIBUTE(QString,Place,comment)
    DECLARE_DATABASEATTRIBUTE(QIcon,Place,icon)

END_ROW_DECLARATION(Place)

START_TABLE_DECLARATION(Place)
END_TABLE_DECLARATION()

#endif // PLACE_H
