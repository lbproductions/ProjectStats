#include "game.h"

#include <QDateTime>

START_TABLE_IMPLEMENTATION(Game)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Game, Game, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,Game,name,"Name")
    IMPLEMENT_DATABASEATTRIBUTE(QString,Game,type,"Type")
    IMPLEMENT_DATABASEATTRIBUTE(bool,Game,live,"Live")
    IMPLEMENT_DATABASEATTRIBUTE(QDateTime,Game,date,"Date")
    IMPLEMENT_DATABASEATTRIBUTE(QTime,Game,length,"Length")
    IMPLEMENT_DATABASEATTRIBUTE(QString,Game,comment,"Comment")
    IMPLEMENT_DATABASEATTRIBUTE(int,Game,siteId,"Site")
}

QString Game::mimeType() const
{
    return "application/projectstats.game";
}

END_ROW_IMPLEMENTATION()
