#include "player.h"

#include <QImage>
#include <QColor>
#include <QDateTime>

#include "game.h"
#include "place.h"

START_TABLE_IMPLEMENTATION(Player)

Player* Players::playerByName(QString name)
{
    QSqlQuery select = query("SELECT id FROM players WHERE name = '"+name+"'");
    if(select.first())
    {
        return rowById(select.value(0).toInt());
    }

    return 0;
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

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Game*,Player,PlayerCalculator,calc,games,tr("Games"))
    Games::instance()->rows()->addDependingAttribute(games);

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Place*,Player,PlayerCalculator,calc,places,tr("Places"))
    Places::instance()->rows()->addDependingAttribute(places);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(QString,int,Player,PlayerCalculator,calc,points,tr("Points"))
    games->addDependingAttribute(points);

    IMPLEMENT_ATTRIBUTE_IN_CALC(double,Player,PlayerCalculator,calc,average,tr("Average"))
    games->addDependingAttribute(average);
    points->addDependingAttribute(average);

    IMPLEMENT_ATTRIBUTE_IN_CALC(int,Player,PlayerCalculator,calc,wins,tr("Wins"))
    games->addDependingAttribute(wins);

    IMPLEMENT_ATTRIBUTE_IN_CALC(int,Player,PlayerCalculator,calc,losses,tr("Losses"))
    games->addDependingAttribute(losses);

    IMPLEMENT_ATTRIBUTE_IN_CALC(QDateTime,Player,PlayerCalculator,calc,lastGame,tr("LastGame"))
    games->addDependingAttribute(lastGame);

    IMPLEMENT_ATTRIBUTE_IN_CALC(QDateTime,Player,PlayerCalculator,calc,lastWin,tr("LastWin"))
    games->addDependingAttribute(lastWin);
    wins->addDependingAttribute(lastWin);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(LiveGame*,double,Player,PlayerCalculator,calc,alcPegel,tr("AlcPegel"))

}

QString Player::mimeType() const
{
    return "application/projectstats.player";
}

QImage Player::calculate_avatar(){
    return QImage(avatarPath->value()).scaledToHeight(30);
}

END_ROW_IMPLEMENTATION()
