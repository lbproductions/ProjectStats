#ifndef DATABASE_PLAYER_H
#define DATABASE_PLAYER_H

#include "psrow.h"

#include <Database/Calculator/playercalculator.h>
#include <Database/Doppelkopf/dokoplayerstats.h>

#include <QDebug>

namespace Gui{
    namespace Details{
        class DetailsWidget;
        class StatsWidget;
        class AbstractPlayerStatsWidget;
    }
}

namespace Database{
    class LiveGameDrink;
    class Place;
}

class QDateTime;

START_ROW_DECLARATION(Player, PSRow)
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
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,liveGameCount)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,offlineGameCount)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,points)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,gamePoints)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,liveGamePoints)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,offlineGamePoints)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,double,Player,PlayerCalculator,average)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,double,Player,PlayerCalculator,weightedAverage)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,double,Player,PlayerCalculator,diffAverageWeightedAverage)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,wins)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,losses)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,double,Player,PlayerCalculator,averagePlacement)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,QDateTime,Player,PlayerCalculator,lastGame)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(QString,QDateTime,Player,PlayerCalculator,lastWin)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(LiveGame*,double,Player,PlayerCalculator,alcPegel)

    Gui::Details::DetailsWidget* detailsWidget();

    Gui::Details::StatsWidget* statsWidget();

    QWidget* typeStatsWidget(QString type);

    DokoPlayerStats* dokoStats();

private:

    DokoPlayerStats* m_dokoStats;


END_ROW_DECLARATION(Player)

START_TABLE_DECLARATION(Player)
    Player* playerByName(QString name);

    MappingAttribute<QString,QList<Player*>,Players, Players> *playersOfType;
    QMap<QString,QList<Player*> > calculate_playersOfType();
END_TABLE_DECLARATION()

#define COMMA ,

Q_DECLARE_METATYPE(QMap<Database::Player* COMMA bool>)
Q_DECLARE_METATYPE(QMap<Database::Player* COMMA double>)
Q_DECLARE_METATYPE(QPair<Database::Player* COMMA Database::Player*>)
Q_DECLARE_METATYPE(QMap<QPair<Database::Player* COMMA Database::Player*> COMMA int>)
Q_DECLARE_METATYPE(QMap<int COMMA QMap<Database::Player* COMMA int> >)
Q_DECLARE_METATYPE(QMap<QString COMMA QList<Database::Player*> >)

#endif // DATABASE_PLAYER_H
