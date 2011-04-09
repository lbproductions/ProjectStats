#include "samplerowchild.h"

START_ROW_IMPLEMENTATION(SampleRowChild, SampleRow, SampleRow)
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,SampleRowChild,child_name)
    IMPLEMENT_DATABASEATTRIBUTE(QString,SampleRowChild,child_type)
}

END_ROW_IMPLEMENTATION()
