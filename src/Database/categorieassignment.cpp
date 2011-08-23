#include "categorieassignment.h"

START_TABLE_IMPLEMENTATION(CategorieAssignment)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(CategorieAssignment, CategorieAssignment, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,CategorieAssignment,categorieId,tr("CategorieId"))
            IMPLEMENT_DATABASEATTRIBUTE(int,CategorieAssignment,elementId,tr("ElementId"))
}

QString CategorieAssignment::mimeType() const
{
    return "application/projectstats.categorieAssignment";
}

END_ROW_IMPLEMENTATION()
