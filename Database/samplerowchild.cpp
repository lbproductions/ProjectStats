#include "samplerowchild.h"

START_ROW_IMPLEMENTATION(SampleRowChild, SampleRow, SampleRow)
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,SampleRowChild,child_name,"child_name")
    IMPLEMENT_DATABASEATTRIBUTE(QString,SampleRowChild,child_type,"child_type")

    IMPLEMENT_ATTRIBUTE(QString,SampleRowChild,string,"String")
}

QString SampleRowChild::mimeType() const
{
    return "application/projectstats.samplerowchild";
}

QString SampleRowChild::calculate_string(){
    return "qwertz";
}

END_ROW_IMPLEMENTATION()
