#include "game.h"

#include <Database/player.h>
#include <Database/position.h>
#include <Database/point.h>
#include <Database/offlinegameinformation.h>

#include "Doppelkopf/dokolivegame.h"
#include "Skat/skatlivegame.h"
#include "offlinegame.h"

#include <QDateTime>

START_TABLE_IMPLEMENTATION(Game)

QPointer<Game> Games::createRowInstance(int id)
{
    Game *row = new Game(id,this);
    Game *row2 = 0;

    if(row->live->value())
    {
	if(row->type->value() == "Doppelkopf")
	{
	    row2 = new DokoLiveGame(id,this);
	}
	else if(row->type->value() == "Skat")
	{
	    row2 = new SkatLiveGame(id,this);
	}
    }
    else{
        row2 = new OfflineGame(id,this);
    }

    if(row2 != 0)
    {
	return row2;
    }

    return row;
}

END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Game, Game, Row)
{
    m_calc = new GameCalculator(this,this);

    IMPLEMENT_DATABASEATTRIBUTE(QString,Game,name,tr("Name"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Game,type,tr("Type"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,Game,live,tr("Live"))
    IMPLEMENT_DATABASEATTRIBUTE(QDateTime,Game,date,tr("Date"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Game,comment,tr("Comment"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Game,siteId,tr("SiteId"))

    IMPLEMENT_ATTRIBUTE(QPointer<Place>,Game,site,tr("Site"))
    siteId->addDependingAttribute(site);

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Player*,Game,GameCalculator,m_calc,players,tr("Players"))
    Positions::instance()->rows()->addDependingAttribute(players);
    OfflineGameInformations::instance()->rows()->addDependingAttribute(players);

    IMPLEMENT_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Game,GameCalculator,placement,tr("Placement"))
    players->addDependingAttribute(placement);

    IMPLEMENT_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Game,GameCalculator,points,tr("Points"))
    Points::instance()->rows()->addDependingAttribute(points);
    OfflineGameInformations::instance()->rows()->addDependingAttribute(points);

    IMPLEMENT_VIRTUAL_LISTATTRIBUTE_IN_CALC(Player*,Game,GameCalculator,playersSortedByPosition,tr("PlayersSortedByPosition"))
    players->addDependingAttribute(playersSortedByPosition);

    IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(QTime,Game,GameCalculator,length,tr("Length"))


}

QString Game::mimeType() const
{
    return "application/projectstats.game";
}

QPointer<Place> Game::calculate_site()
{
    return Places::instance()->rowById(this->siteId->value());
}


END_ROW_IMPLEMENTATION()
