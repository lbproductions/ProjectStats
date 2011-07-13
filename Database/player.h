#ifndef DATABASE_PLAYER_H
#define DATABASE_PLAYER_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"
#include "listattribute.h"
#include "mappingattribute.h"

#include <Database/Calculator/playercalculator.h>

#include <QDebug>

namespace Gui{
    namespace Details{
        class DetailsWidget;
        class StatsWidget;
        class AbstractPlayerStatsWidget;
    }
}

namespace Database{
    class Place;
}

class QDateTime;

START_ROW_DECLARATION(Player, Row)
    DECLARE_ROW_CONSTRUCTORS(Player, Player)

    DECLARE_DATABASEATTRIBUTE(QString,Player,name)
    DECLARE_DATABASEATTRIBUTE(QString,Player,gender)
    DECLARE_DATABASEATTRIBUTE(int,Player,weight)
    DECLARE_DATABASEATTRIBUTE(int,Player,size)
    DECLARE_DATABASEATTRIBUTE(QColor,Player,color)
    DECLARE_DATABASEATTRIBUTE(QString,Player,avatarPath)

    DECLARE_ATTRIBUTE(QImage,Player,avatar)

    DECLARE_LISTATTRIBUTE_IN_CALC(Game*,Player,PlayerCalculator,games)
    DECLARE_LISTATTRIBUTE_IN_CALC(Place*,Player,PlayerCalculator,places)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,gameCount)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,points)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,double,Player,PlayerCalculator,average)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,wins)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,losses)

    DECLARE_ATTRIBUTE_IN_CALC(QDateTime,Player,PlayerCalculator,lastGame)
    DECLARE_ATTRIBUTE_IN_CALC(QDateTime,Player,PlayerCalculator,lastWin)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(LiveGame*,double,Player,PlayerCalculator,alcPegel)

    Gui::Details::DetailsWidget* detailsWidget();

    Gui::Details::StatsWidget* statsWidget();

    Gui::Details::AbstractPlayerStatsWidget* typeStatsWidget(QString type);


END_ROW_DECLARATION(Player)

START_TABLE_DECLARATION(Player)
    Player* playerByName(QString name);
END_TABLE_DECLARATION()

#endif // DATABASE_PLAYER_H
