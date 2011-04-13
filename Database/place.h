#ifndef DATABASE_PLACE_H
#define DATABASE_PLACE_H

#include <QPointer>

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

#include "player.h"

START_ROW_DECLARATION(Place, Row)
    DECLARE_ROW_CONSTRUCTORS(Place, Place)

    DECLARE_DATABASEATTRIBUTE(int,Place,playerId)
    DECLARE_DATABASEATTRIBUTE(int,Place,plz)
    DECLARE_DATABASEATTRIBUTE(QString,Place,ort)
    DECLARE_DATABASEATTRIBUTE(QString,Place,strasse)
    DECLARE_DATABASEATTRIBUTE(int,Place,nummer)
    DECLARE_DATABASEATTRIBUTE(QString,Place,comment)
    DECLARE_DATABASEATTRIBUTE(QString,Place,iconPath)

    DECLARE_ATTRIBUTE(QPointer<Player>, Place, player)
    DECLARE_ATTRIBUTE(QImage,Place,icon)


END_ROW_DECLARATION(Place)

START_TABLE_DECLARATION(Place)
END_TABLE_DECLARATION()

Q_DECLARE_METATYPE(QPointer<Database::Player>)

#endif // PLACE_H
