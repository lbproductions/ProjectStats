#include "player.h"

#include <QImage>
#include <QColor>

START_TABLE_IMPLEMENTATION(Player)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Player, Player, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,Player,name,"Name")
    IMPLEMENT_DATABASEATTRIBUTE(QString,Player,gender,"Gender")
    IMPLEMENT_DATABASEATTRIBUTE(int,Player,weight, "Weight")
    IMPLEMENT_DATABASEATTRIBUTE(int,Player,size, "Size")
    IMPLEMENT_DATABASEATTRIBUTE(QColor,Player,color, "Color")
    color->setRole(Qt::DecorationRole);
    IMPLEMENT_DATABASEATTRIBUTE(QString,Player,avatarPath, "AvatarPath")
    IMPLEMENT_DATABASEATTRIBUTE(int,Player,residenceId, "Residence")

    IMPLEMENT_ATTRIBUTE(QImage,Player,avatar,tr("Avatar"))
    avatarPath->addDependingAttribute(avatar);
    avatar->setRole(Qt::DecorationRole);
}

QString Player::mimeType() const
{
    return "application/projectstats.player";
}

QImage Player::calculate_avatar(){
    return QImage(avatarPath->value());
}

END_ROW_IMPLEMENTATION()
