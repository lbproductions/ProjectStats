#include "player.h"

#include <QImage>
#include <QColor>

#include "game.h"
#include "place.h"

START_TABLE_IMPLEMENTATION(Player)
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

    IMPLEMENT_ATTRIBUTE_IN_CALC(QList<Game*>,Player,PlayerCalculator,calc,games,"Games")
    Games::instance()->rows()->addDependingAttribute(games);

    IMPLEMENT_ATTRIBUTE_IN_CALC(QList<Place*>,Player,PlayerCalculator,calc,places,"Places")
    Places::instance()->rows()->addDependingAttribute(places);

    IMPLEMENT_ATTRIBUTE_IN_CALC(int,Player,PlayerCalculator,calc,points,"Points")
}

QString Player::mimeType() const
{
    return "application/projectstats.player";
}

QImage Player::calculate_avatar(){
    return QImage(avatarPath->value());
}

END_ROW_IMPLEMENTATION()
