#include "place.h"

#include <QIcon>

START_TABLE_IMPLEMENTATION(Place)
END_ROW_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Place, Place, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,Place,playerId,"Player")
    IMPLEMENT_DATABASEATTRIBUTE(int,Place,plz,"PLZ")
    IMPLEMENT_DATABASEATTRIBUTE(QString,Place,ort,"Ort")
    IMPLEMENT_DATABASEATTRIBUTE(QString,Place,strasse,"Strasse")
    IMPLEMENT_DATABASEATTRIBUTE(int,Place,nummer,"Nr")
    IMPLEMENT_DATABASEATTRIBUTE(QString,Place,comment,"Comment")
    IMPLEMENT_DATABASEATTRIBUTE(QIcon,Place,icon,"Icon")
    icon->setRole(Qt::DecorationRole);
}

QString Place::mimeType() const
{
    return "application/projectstats.place";
}

END_ROW_IMPLEMENTATION()
