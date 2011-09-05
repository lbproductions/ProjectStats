#include "game.h"

#include <Database/player.h>
#include <Database/position.h>
#include <Database/point.h>
#include <Database/offlinegameinformation.h>

#include "Doppelkopf/dokolivegame.h"
#include "Skat/skatlivegame.h"
#include "offlinegame.h"

#include <Gui/Details/rowwindow.h>
#include <Gui/Details/GameDetails/gamedetailswidget.h>
#include <Gui/Details/GameDetails/gamesummarywidget.h>

#include <QDateTime>

namespace Database {
IMPLEMENT_SINGLETON( Games )
Games::Games() :
    Table<Game>(QString("games"))
{
    types = new ListAttribute<QString,Games, Games>("types",tr("Types"), this);
    types->setCalculationFunction(this,&Games::calculate_types);
    this->rows()->addDependingAttribute(types);

    unfinishedGames = new ListAttribute<Game*,Games, Games>("unfinishedGames",tr("Unfinished Games"), this);
    unfinishedGames->setCalculationFunction(this,&Games::calculate_unfinishedGames);
    this->rows()->addDependingAttribute(unfinishedGames);
}
REGISTER_TABLE(Games)

QPointer<Game> Games::createRowInstance(int id)
{
    Game *row = new Game(id,this);
    Game *row2 = 0;

    if(row->live->value())
    {
        if(row->type->value() == DokoLiveGame::TYPE)
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
        row->deleteLater();
	return row2;
    }

    return row;
}

QStringList Games::possibleTypes() const
{
    QStringList list;
    list << DokoLiveGame::TYPE;
    list << "Skat";
    return list;
}

QList<QString> Games::calculate_types(){
    QList<QString> list;
    foreach(Game* g, Games::instance()->allRows()){
        if(!list.contains(g->type->value())){
            list.append(g->type->value());
        }
    }
    return list;
}

QList<Game*> Games::calculate_unfinishedGames(){
    QList<Game*> list;
    foreach(Game* g, Games::instance()->allRows()){
        if(g->state->value() == Round::PausedState || g->state->value() == Round::RunningState){
            list.append(g);
        }
    }
    return list;
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

    IMPLEMENT_VIRTUAL_LISTATTRIBUTE_IN_CALC(Player*,Game,GameCalculator,playersSortedByPlacement,tr("PlayersSortedByPlacement"))
    players->addDependingAttribute(playersSortedByPlacement);

    IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(QTime,Game,GameCalculator,length,tr("Length"))

    IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(Round::RoundState,Game,GameCalculator,state,tr("State"))
    state->setRole(Qt::DecorationRole);
}

Game::Game(QString type, bool live) :
    Row(0,Games::instance())
{
    initializeAttributes();

    this->type->setValue(type);
    this->live->setValue(live);
}

QString Game::mimeType() const
{
    return "application/projectstats.game";
}

QPointer<Place> Game::calculate_site()
{
    QPointer<Place> pointer = Places::instance()->rowById(siteId->value());
    return pointer;
}

Gui::Details::SummaryWidget* Game::summaryWidget(){
    return new Gui::Details::GameDetails::GameSummaryWidget(this);
}

Gui::Details::DetailsWidget* Game::detailsWidget(){
    return new Gui::Details::GameDetailsWidget(this);
}

Gui::Details::RowWindow* Game::detailsWindow()
{
    return new Gui::Details::RowWindow(this);
}

void Game::addPlayer(Player* /*player*/)
{
    qWarning() << "Game::addPlayer: You must not call addPlayer() on a Game!";
}

END_ROW_IMPLEMENTATION()
