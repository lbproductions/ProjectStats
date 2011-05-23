#ifndef DATABASE_GAME_H
#define DATABASE_GAME_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"
#include "mappingattribute.h"
#include "attributehash.h"
#include "listattribute.h"

#include "place.h"

#include <Database/Calculator/gamecalculator.h>

namespace Database{
    class Player;
    class Games;
}

START_ROW_DECLARATION(Game, Row)
    DECLARE_ROW_CONSTRUCTORS(Game, Game)

    GameCalculator* m_calc;

    DECLARE_DATABASEATTRIBUTE(QString,Game,name)
    DECLARE_DATABASEATTRIBUTE(QString,Game,type)
    DECLARE_DATABASEATTRIBUTE(bool,Game,live)
    DECLARE_DATABASEATTRIBUTE(QDateTime,Game,date)
    DECLARE_DATABASEATTRIBUTE(QString,Game,comment)
    DECLARE_DATABASEATTRIBUTE(int,Game,siteId)

    DECLARE_ATTRIBUTE(QPointer<Place>,Game,site)

    DECLARE_LISTATTRIBUTE_IN_CALC(Player*,Game,GameCalculator,players)
    DECLARE_VIRTUAL_LISTATTRIBUTE_IN_CALC(Player*,Game,GameCalculator,playersSortedByPosition)

    DECLARE_VIRTUAL_ATTRIBUTE_IN_CALC(QTime,Game,GameCalculator,length)
    DECLARE_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Game,GameCalculator,placement)
    DECLARE_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Game,GameCalculator,points)


END_ROW_DECLARATION(Game)

START_TABLE_DECLARATION(Game)
QPointer<Game> createRowInstance(int id);
END_TABLE_DECLARATION()

Q_DECLARE_METATYPE(QPointer<Database::Place>)

#endif // DATABASE_GAME_H
