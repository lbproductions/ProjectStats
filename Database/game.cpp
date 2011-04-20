#include "game.h"

#include <Database/player.h>
#include <Database/position.h>
#include <Database/offlinegameinformation.h>

#include <QDateTime>

START_TABLE_IMPLEMENTATION(Game)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Game, Game, Row)
{
    GameCalculator* calc = new GameCalculator(this,this);

    IMPLEMENT_DATABASEATTRIBUTE(QString,Game,name,tr("Name"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Game,type,tr("Type"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,Game,live,tr("Live"))
    IMPLEMENT_DATABASEATTRIBUTE(QDateTime,Game,date,tr("Date"))
    IMPLEMENT_DATABASEATTRIBUTE(QTime,Game,length,tr("Length"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Game,comment,tr("Comment"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Game,siteId,tr("SiteId"))

    IMPLEMENT_ATTRIBUTE(QPointer<Place>,Game,site,tr("Site"))
    siteId->addDependingAttribute(site);

    IMPLEMENT_ATTRIBUTE_IN_CALC(QList<Player*>,Game,GameCalculator,calc,players,"Players")
    Positions::instance()->rows()->addDependingAttribute(players);
    OfflineGameInformations::instance()->rows()->addDependingAttribute(players);


}

QString Game::mimeType() const
{
    return "application/projectstats.game";
}

QPointer<Place> Game::calculate_site(){
    return Places::instance()->rowById(this->siteId->value());
}

END_ROW_IMPLEMENTATION()
