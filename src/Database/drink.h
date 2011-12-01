#ifndef DATABASE_DRINK_H
#define DATABASE_DRINK_H

#include <LBDatabase/LBDatabase.h>

namespace Database {
    class DrinkCalculator;
    class Player;
}

START_ROW_DECLARATION(Drink, Row)
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

    QWidget* detailsWidget();

END_ROW_DECLARATION(Drink)

START_TABLE_DECLARATION(Drink)

ListAttribute<QString,Drinks, Drinks> *types;
QList<QString> calculate_types();

MappingAttribute<QString,QList<Drink*>,Drinks,Drinks > *drinksOfType;
QMap<QString,QList<Drink*> > calculate_drinksOfType();

END_TABLE_DECLARATION()

Q_DECLARE_METATYPE(QMap<QString COMMA QList<Database::Drink*> >)

#endif // DATABASE_DRINK_H
