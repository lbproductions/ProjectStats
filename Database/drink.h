#ifndef DATABASE_DRINK_H
#define DATABASE_DRINK_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

START_ROW_DECLARATION(Drink)
    DECLARE_ROW_CONSTRUCTORS(Drink)

    DECLARE_DATABASEATTRIBUTE(QString,Drink,name)
    DECLARE_DATABASEATTRIBUTE(QString,Drink,type)

    DECLARE_ATTRIBUTE_WITH_UPDATEFUNCTION(QString, Drink, test)

    DECLARE_ATTRIBUTE(QString, Drink, test2)
    QString update_test2_test();

    DECLARE_ATTRIBUTE(QList<Drink*>, Drink, drinks)

END_ROW_DECLARATION(Drink)

DECLARE_TABLE(Drink)

#endif // DATABASE_DRINK_H
