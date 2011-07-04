#ifndef DATABASE_PLACE_H
#define DATABASE_PLACE_H

#include <QPointer>

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

#include "player.h"

#include <Database/Calculator/placecalculator.h>

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

    DECLARE_ATTRIBUTE_IN_CALC(int,Place,PlaceCalculator,gameCount)

    DECLARE_ATTRIBUTE(QString,Place,displayString)

    Gui::Details::DetailsWidget* detailsWidget();

END_ROW_DECLARATION(Place)

START_TABLE_DECLARATION(Place)
END_TABLE_DECLARATION()

#endif // PLACE_H
