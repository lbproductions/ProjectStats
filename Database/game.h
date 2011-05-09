#ifndef DATABASE_GAME_H
#define DATABASE_GAME_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"
#include "mappingattribute.h"
#include "attributehash.h"

#include "place.h"

#include <Database/Calculator/gamecalculator.h>

namespace Database{
    class Player;
    class Games;
}

START_ROW_DECLARATION(Game, Row)
    DECLARE_ROW_CONSTRUCTORS(Game, Game)

    DECLARE_DATABASEATTRIBUTE(QString,Game,name)
    DECLARE_DATABASEATTRIBUTE(QString,Game,type)
    DECLARE_DATABASEATTRIBUTE(bool,Game,live)
    DECLARE_DATABASEATTRIBUTE(QDateTime,Game,date)
    DECLARE_DATABASEATTRIBUTE(QTime,Game,length)
    DECLARE_DATABASEATTRIBUTE(QString,Game,comment)
    DECLARE_DATABASEATTRIBUTE(int,Game,siteId)

    DECLARE_ATTRIBUTE(QPointer<Place>,Game,site)
    DECLARE_ATTRIBUTE_IN_CALC(QList<Player*>,Game,GameCalculator,players)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Game,GameCalculator,placement)


END_ROW_DECLARATION(Game)

START_TABLE_DECLARATION(Game)
END_TABLE_DECLARATION()

#define COMMA ,

Q_DECLARE_METATYPE(QPointer<Database::Place>)
Q_DECLARE_METATYPE(Database::AttributeHash<Database::Player* COMMA int>*)

#endif // DATABASE_GAME_H
