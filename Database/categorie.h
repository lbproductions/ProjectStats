#ifndef DATABASE_CATEGORIE_H
#define DATABASE_CATEGORIE_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

START_ROW_DECLARATION(Categorie, Row)
    DECLARE_ROW_CONSTRUCTORS(Categorie, Categorie)

    DECLARE_DATABASEATTRIBUTE(QString,Categorie,name)
    DECLARE_DATABASEATTRIBUTE(QString,Categorie,icon)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,parentId)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,type)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,orderIndicator)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,contentType)


END_ROW_DECLARATION(Categorie)

START_TABLE_DECLARATION(Categorie)
END_TABLE_DECLARATION()

#endif // DATABASE_CATEGORIE_H
