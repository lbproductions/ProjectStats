#ifndef DATABASE_DRINK_H
#define DATABASE_DRINK_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"
#include "listattribute.h"
#include "mappingattribute.h"

#include <Database/Calculator/drinkcalculator.h>

#include <Database/Calculator/drinkcalculator.h>

START_ROW_DECLARATION(Drink, Row)
#if QT_VERSION >= 0x050000
    Q_OBJECT
#endif

    DECLARE_ROW_CONSTRUCTORS(Drink, Drink)

    DECLARE_DATABASEATTRIBUTE(QString,Drink,name)
    DECLARE_DATABASEATTRIBUTE(QString,Drink,type)
    DECLARE_DATABASEATTRIBUTE(double,Drink,size)
    DECLARE_DATABASEATTRIBUTE(QString,Drink,iconPath)
    DECLARE_DATABASEATTRIBUTE(double,Drink,alc)

    DECLARE_ATTRIBUTE(QImage,Drink,icon)

    DECLARE_ATTRIBUTE_IN_CALC(int,Drink,DrinkCalculator,drinkCount)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Drink,DrinkCalculator,countPerPlayer)
    DECLARE_ATTRIBUTE_IN_CALC(QString,Drink,DrinkCalculator,mostDrinks)

    Gui::Details::DetailsWidget* detailsWidget();

END_ROW_DECLARATION(Drink)

START_TABLE_DECLARATION(Drink)

ListAttribute<QString,Drinks, Drinks> *types;
QList<QString> calculate_types();

MappingAttribute<QString,QList<Drink*>,Drinks,Drinks > *drinksOfType;
QMap<QString,QList<Drink*> > calculate_drinksOfType();

END_TABLE_DECLARATION()

#endif // DATABASE_DRINK_H
