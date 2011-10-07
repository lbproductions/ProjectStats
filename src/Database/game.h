#ifndef DATABASE_GAME_H
#define DATABASE_GAME_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"
#include "mappingattribute.h"
#include "listattribute.h"

#include "place.h"
#include "round.h"

#include <Database/Calculator/gamecalculator.h>

namespace Database{
    class Player;
    class Games;
}

START_ROW_DECLARATION(Game, Row)
    DECLARE_ROW_CONSTRUCTORS(Game, Game)

    Game(QString type, bool live);

    GameCalculator* m_calc;

    DECLARE_DATABASEATTRIBUTE(QString,Game,name)
    DECLARE_DATABASEATTRIBUTE(QString,Game,type)
    DECLARE_DATABASEATTRIBUTE(bool,Game,live)
    DECLARE_DATABASEATTRIBUTE(QDateTime,Game,date)
    DECLARE_DATABASEATTRIBUTE(QString,Game,comment)
    DECLARE_DATABASEATTRIBUTE(int,Game,siteId)

    DECLARE_ATTRIBUTE(QPointer<Place>,Game,site)
    DECLARE_VIRTUAL_ATTRIBUTE_IN_CALC(Round::RoundState,Game,GameCalculator,state)

    DECLARE_LISTATTRIBUTE_IN_CALC(Player*,Game,GameCalculator,players)
    DECLARE_VIRTUAL_LISTATTRIBUTE_IN_CALC(Player*,Game,GameCalculator,playersSortedByPosition)
    DECLARE_VIRTUAL_LISTATTRIBUTE_IN_CALC(Player*,Game,GameCalculator,playersSortedByPlacement)

    DECLARE_VIRTUAL_ATTRIBUTE_IN_CALC(QTime,Game,GameCalculator,length)
    DECLARE_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Game,GameCalculator,placement)
    DECLARE_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Game,GameCalculator,points)

    Gui::Details::SummaryWidget* summaryWidget();

    virtual Gui::Details::DetailsWidget* detailsWidget();

    virtual Gui::Details::RowWindow* detailsWindow();

    virtual void addPlayer(Player* player);

END_ROW_DECLARATION(Game)

START_TABLE_DECLARATION(Game)

    QPointer<Game> createRowInstance(int id);

    QStringList possibleTypes() const;

    ListAttribute<QString,Games, Games> *types;
    QList<QString> calculate_types();

    ListAttribute<Game*,Games, Games> *unfinishedGames;
    QList<Game*> calculate_unfinishedGames();

    MappingAttribute<QString,QList<Game*>,Games, Games> *gamesOfType;
    QMap<QString,QList<Game*> > calculate_gamesOfType();

END_TABLE_DECLARATION()

Q_DECLARE_METATYPE(QPointer<Database::Place>)

#endif // DATABASE_GAME_H
