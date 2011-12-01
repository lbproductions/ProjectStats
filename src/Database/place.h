#ifndef DATABASE_PLACE_H
#define DATABASE_PLACE_H

#include "psrow.h"

#include <Database/Calculator/placecalculator.h>

START_ROW_DECLARATION(Place, PSRow)
    DECLARE_ROW_CONSTRUCTORS(Place, Place)

    DECLARE_DATABASEATTRIBUTE(int,Place,plz)
    DECLARE_DATABASEATTRIBUTE(QString,Place,ort)
    DECLARE_DATABASEATTRIBUTE(QString,Place,strasse)
    DECLARE_DATABASEATTRIBUTE(int,Place,nummer)
    DECLARE_DATABASEATTRIBUTE(QString,Place,comment)
    DECLARE_DATABASEATTRIBUTE(QString,Place,iconPath)

    OneToManyRelation<Place, Player>* players;
    DECLARE_ATTRIBUTE(QImage,Place,icon)

    DECLARE_ATTRIBUTE_IN_CALC(int,Place,PlaceCalculator,gameCount)

    DECLARE_ATTRIBUTE(QString,Place,displayString)

    Gui::Details::DetailsWidget* detailsWidget();

END_ROW_DECLARATION(Place)

START_TABLE_DECLARATION(Place)
END_TABLE_DECLARATION()

#endif // PLACE_H
