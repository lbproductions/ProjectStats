#ifndef DATABASE_DRINK_H
#define DATABASE_DRINK_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

#include <Database/Calculator/drinkcalculator.h>

START_ROW_DECLARATION(Drink, Row)
    DECLARE_ROW_CONSTRUCTORS(Drink, Drink)

    DECLARE_DATABASEATTRIBUTE(QString,Drink,name)
    DECLARE_DATABASEATTRIBUTE(QString,Drink,type)
    DECLARE_DATABASEATTRIBUTE(double,Drink,size)
    DECLARE_DATABASEATTRIBUTE(QString,Drink,iconPath)
    DECLARE_DATABASEATTRIBUTE(double,Drink,alc)

    DECLARE_ATTRIBUTE_WITH_UPDATEFUNCTION(QString, Drink, test)

    DECLARE_ATTRIBUTE(QString, Drink, test2)
    QString update_test2_test();

    DECLARE_ATTRIBUTE(QImage,Drink,icon)

    DECLARE_ATTRIBUTE(QList<Drink*>, Drink, drinks)

    DECLARE_ATTRIBUTE_IN_CALC(int,Drink,DrinkCalculator,drinkCount)

END_ROW_DECLARATION(Drink)

START_TABLE_DECLARATION(Drink)
END_TABLE_DECLARATION()

#endif // DATABASE_DRINK_H
