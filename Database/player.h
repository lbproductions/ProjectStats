#ifndef DATABASE_PLAYER_H
#define DATABASE_PLAYER_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"
#include "listattribute.h"

#include <Database/Calculator/playercalculator.h>

#include <QDebug>

namespace Database{
    class Place;
}

class QDateTime;

START_ROW_DECLARATION(Player, Row)
    DECLARE_ROW_CONSTRUCTORS(Player, Player)

    DECLARE_DATABASEATTRIBUTE(QString,Player,name)
    DECLARE_DATABASEATTRIBUTE(QString,Player,gender)
    DECLARE_DATABASEATTRIBUTE(int,Player,weight)
    DECLARE_DATABASEATTRIBUTE(int,Player,size)
    DECLARE_DATABASEATTRIBUTE(QColor,Player,color)
    DECLARE_DATABASEATTRIBUTE(QString,Player,avatarPath)

    DECLARE_ATTRIBUTE(QImage,Player,avatar)

    DECLARE_LISTATTRIBUTE_IN_CALC(Game*,Player,PlayerCalculator,games)
    DECLARE_LISTATTRIBUTE_IN_CALC(Place*,Player,PlayerCalculator,places)

    DECLARE_ATTRIBUTE_IN_CALC(int,Player,PlayerCalculator,points)
    DECLARE_ATTRIBUTE_IN_CALC(double,Player,PlayerCalculator,average)
    DECLARE_ATTRIBUTE_IN_CALC(int,Player,PlayerCalculator,wins)
    DECLARE_ATTRIBUTE_IN_CALC(int,Player,PlayerCalculator,losses)

    DECLARE_ATTRIBUTE_IN_CALC(QDateTime,Player,PlayerCalculator,lastGame)
    DECLARE_ATTRIBUTE_IN_CALC(QDateTime,Player,PlayerCalculator,lastWin)


END_ROW_DECLARATION(Player)

START_TABLE_DECLARATION(Player)
END_TABLE_DECLARATION()

#endif // DATABASE_PLAYER_H
