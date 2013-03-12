#ifndef DATABASE_CATEGORIEASSIGNMENT_H
#define DATABASE_CATEGORIEASSIGNMENT_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

START_ROW_DECLARATION(CategorieAssignment, Row)
#if QT_VERSION >= 0x050000
    Q_OBJECT
#endif
    DECLARE_ROW_CONSTRUCTORS(CategorieAssignment, CategorieAssignment)

    DECLARE_DATABASEATTRIBUTE(int,CategorieAssignment,categorieId)
    DECLARE_DATABASEATTRIBUTE(int,CategorieAssignment,elementId)


END_ROW_DECLARATION(CategorieAssignment)

START_TABLE_DECLARATION(CategorieAssignment)
END_TABLE_DECLARATION()

#endif // DATABASE_CATEGORIEASSIGNMENT_H
