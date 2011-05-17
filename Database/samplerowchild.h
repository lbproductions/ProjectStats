#ifndef DATABASE_SAMPLEROWCHILD_H
#define DATABASE_SAMPLEROWCHILD_H

#include "samplerow.h"

#include "row.h"
#include "table.h"
#include "databaseattribute.h"

#include "drink.h"


START_ROW_DECLARATION(SampleRowChild, SampleRow)
    DECLARE_ROW_CONSTRUCTORS(SampleRowChild, SampleRow)

    DECLARE_DATABASEATTRIBUTE(QString,SampleRowChild,child_name)
    DECLARE_DATABASEATTRIBUTE(QString,SampleRowChild,child_type)

    DECLARE_ATTRIBUTE(QString,SampleRowChild,string)

END_ROW_DECLARATION(SampleRowChild)

#endif // DATABASE_SAMPLEROWCHILD_H
