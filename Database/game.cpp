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
    IMPLEMENT_DATABASEATTRIBUTE(int,Game,siteId,"SiteId")

    IMPLEMENT_ATTRIBUTE(QPointer<Place>,Game,site,"Site")
    siteId->addDependingAttribute(site);
}

QString Game::mimeType() const
{
    return "application/projectstats.game";
}

QPointer<Place> Game::calculate_site(){
    return Places::instance()->rowById(this->siteId->value());
}

END_ROW_IMPLEMENTATION()
