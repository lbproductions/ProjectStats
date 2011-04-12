#include "categorie.h"

START_TABLE_IMPLEMENTATION(Categorie)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Categorie, Categorie, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,Categorie,name,tr("Name"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Categorie,icon,tr("Icon"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Categorie,parentId,tr("parentId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Categorie,type,tr("Type"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Categorie,orderIndicator,tr("OrderIndicator"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Categorie,contentType,tr("ContentType"))
}

QString Categorie::mimeType() const
{
    return "application/projectstats.categorie";
}

END_ROW_IMPLEMENTATION()
