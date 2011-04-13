#ifndef DATABASE_PLAYER_H
#define DATABASE_PLAYER_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

#include <QDebug>

START_ROW_DECLARATION(Player, Row)
    DECLARE_ROW_CONSTRUCTORS(Player, Player)

    DECLARE_DATABASEATTRIBUTE(QString,Player,name)
    DECLARE_DATABASEATTRIBUTE(QString,Player,gender)
    DECLARE_DATABASEATTRIBUTE(int,Player,weight)
    DECLARE_DATABASEATTRIBUTE(int,Player,size)
    DECLARE_DATABASEATTRIBUTE(QColor,Player,color)
    DECLARE_DATABASEATTRIBUTE(QString,Player,avatarPath)
    DECLARE_DATABASEATTRIBUTE(int,Player,residenceId)

    DECLARE_ATTRIBUTE(QImage,Player,avatar)

END_ROW_DECLARATION(Player)

START_TABLE_DECLARATION(Player)
END_TABLE_DECLARATION()

#endif // DATABASE_PLAYER_H
