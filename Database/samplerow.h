#ifndef DATABASE_SAMPLEROW_H
#define DATABASE_SAMPLEROW_H

#include "row.h"
#include "table.h"
#include "databaseattribute.h"

#include "drink.h"


START_ROW_DECLARATION(SampleRow /*Name der Row*/, Row /*Superklasse der Row*/)
    DECLARE_ROW_CONSTRUCTORS(SampleRow /*Name der Row*/, SampleRow /*Name der Basisklasse der Row (z.B. Game für alle games)*/)

    DECLARE_DATABASEATTRIBUTE(QString /*Typ*/,SampleRow /*Name der Row*/,name /*Name des attributs*/)
    DECLARE_DATABASEATTRIBUTE(QString,SampleRow,type)

    DECLARE_ATTRIBUTE_WITH_UPDATEFUNCTION(QString, SampleRow, test)

    DECLARE_ATTRIBUTE(QString, SampleRow, test2)
    QString update_test2_test();

    DECLARE_ATTRIBUTE(QList<Drink*>, SampleRow, drinks)

END_ROW_DECLARATION(SampleRow)

START_TABLE_DECLARATION(SampleRow)
    QPointer<SampleRow> createRowInstance(int id);
END_TABLE_DECLARATION()

#endif // DATABASE_SAMPLEROW_H
