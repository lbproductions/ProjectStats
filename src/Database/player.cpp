#include "player.h"

#include <QImage>
#include <QColor>
#include <QDateTime>

#include "game.h"
#include "place.h"
#include "livegamedrink.h"

#include <Gui/Details/PlayerDetails/playerdetailswidget.h>
#include <Gui/Details/PlayerDetails/playerstatswidget.h>
#include <Gui/Details/PlayerDetails/abstractplayerstatswidget.h>
#include <Gui/Details/PlayerDetails/dokoplayerstatswidget.h>

namespace Database {
IMPLEMENT_SINGLETON( Players )
Players::Players() :
    Table<Player>(QString("players"))
{
    playersOfType = new MappingAttribute<QString,QList<Player*>,Players, Players>("playersOfType",tr("PlayersOfType"), this);
    playersOfType->setCalculationFunction(this,&Players::calculate_playersOfType);
    this->rows()->addDependingAttribute(playersOfType);
}
REGISTER_TABLE(Players)

Player* Players::playerByName(QString name)
{
    QSqlQuery select = query("SELECT id FROM players WHERE name = '"+name+"'");
    if(select.first())
    {
        return rowById(select.value(0).toInt());
    }

    return 0;
}

QMap<QString,QList<Player*> > Players::calculate_playersOfType(){
    QMap<QString,QList<Player*> > map;
    foreach(QString type, Games::instance()->types->value()){
        QList<Player*> list;
        foreach(Player* p, Players::instance()->allRows()){
            if(p->gameCount->value(type) > 0){
               list.append(p);
            }
        }
        map.insert(type,list);
    }
    return map;
}

END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Player, Player, Row)
{

    PlayerCalculator* calc = new PlayerCalculator(this,this);

    IMPLEMENT_DATABASEATTRIBUTE(QString,Player,name,tr("Name"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Player,gender,tr("Gender"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Player,weight, tr("Weight"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Player,size, tr("Size"))
    IMPLEMENT_DATABASEATTRIBUTE(QColor,Player,color, tr("Color"))
    color->setRole(Qt::DecorationRole);
    IMPLEMENT_DATABASEATTRIBUTE(QString,Player,avatarPath, tr("AvatarPath"))

    IMPLEMENT_ATTRIBUTE(QImage,Player,avatar,tr("Avatar"))
    avatarPath->addDependingAttribute(avatar);
    avatar->setRole(Qt::DecorationRole);

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Game*,Player,PlayerCalculator,calc,games,tr("GameList"))
    Games::instance()->rows()->addDependingAttribute(games);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,calc,gameCount,tr("Games"))
    games->addDependingAttribute(gameCount);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,calc,liveGameCount,tr("LiveGames"))
    games->addDependingAttribute(liveGameCount);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,calc,offlineGameCount,tr("OfflineGames"))
    games->addDependingAttribute(offlineGameCount);

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Place*,Player,PlayerCalculator,calc,places,tr("Places"))
    Places::instance()->rows()->addDependingAttribute(places);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,calc,points,tr("Points"))
    games->addDependingAttribute(points);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,calc,offlineGamePoints,tr("OfflineGamePoints"))
    games->addDependingAttribute(offlineGamePoints);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,calc,liveGamePoints,tr("LiveGamePoints"))
    games->addDependingAttribute(liveGamePoints);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,calc,gamePoints,tr("GamePoints"))
    offlineGamePoints->addDependingAttribute(gamePoints);
    liveGamePoints->addDependingAttribute(gamePoints);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,double,Player,PlayerCalculator,calc,average,tr("Average"))
    games->addDependingAttribute(average);
    points->addDependingAttribute(average);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,calc,wins,tr("Wins"))
    games->addDependingAttribute(wins);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,calc,losses,tr("Losses"))
    games->addDependingAttribute(losses);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,QDateTime,Player,PlayerCalculator,calc,lastGame,tr("LastGame"))
    games->addDependingAttribute(lastGame);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,QDateTime,Player,PlayerCalculator,calc,lastWin,tr("LastWin"))
    games->addDependingAttribute(lastWin);
    wins->addDependingAttribute(lastWin);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(LiveGame*,double,Player,PlayerCalculator,calc,alcPegel,tr("AlcPegel"))

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,double,Player,PlayerCalculator,calc,averagePlacement,tr("LiveAveragePlacement"))
    games->addDependingAttribute(averagePlacement);

    m_dokoStats = new DokoPlayerStats(this);

}

QString Player::mimeType() const
{
    return "application/projectstats.player";
}

QImage Player::calculate_avatar()
{
    QImage image(avatarPath->value());
    if(!image.isNull())
    {
        return image.scaledToHeight(30);
    }
    return QImage();
}

Gui::Details::DetailsWidget* Player::detailsWidget(){
    return new Gui::Details::PlayerDetailsWidget(this);
}

Gui::Details::StatsWidget* Player::statsWidget(){
    return new Gui::Details::PlayerStatsWidget(this);
}

Gui::Details::AbstractPlayerStatsWidget* Player::typeStatsWidget(QString type){
    if(type == "Doppelkopf"){
        return new Gui::Details::DokoPlayerStatsWidget(this);
    }
    return new Gui::Details::AbstractPlayerStatsWidget(this,type);
}

DokoPlayerStats* Player::dokoStats(){
    if(m_dokoStats.isNull()){
        m_dokoStats = new DokoPlayerStats(this);
    }
    return m_dokoStats;
}

END_ROW_IMPLEMENTATION()
