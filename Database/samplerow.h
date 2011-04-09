#ifndef DATABASE_SAMPLEROW_H
#define DATABASE_SAMPLEROW_H

#include "row.h"
#include "table.h"
#include "databaseattribute.h"

#include "drink.h"


START_ROW_DECLARATION(SampleRow, Row)
    DECLARE_ROW_CONSTRUCTORS(SampleRow, SampleRow)

    DECLARE_DATABASEATTRIBUTE(QString,SampleRow,name)
    DECLARE_DATABASEATTRIBUTE(QString,SampleRow,type)

    DECLARE_ATTRIBUTE_WITH_UPDATEFUNCTION(QString, SampleRow, test)

    DECLARE_ATTRIBUTE(QString, SampleRow, test2)
    QString update_test2_test();

    DECLARE_ATTRIBUTE(QList<Drink*>, SampleRow, drinks)

END_ROW_DECLARATION(SampleRow)

DECLARE_TABLE(SampleRow)

#endif // DATABASE_SAMPLEROW_H
