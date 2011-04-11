#include "player.h"

#include <QIcon>

START_TABLE_IMPLEMENTATION(Player)
END_ROW_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Player, Player, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,Player,name,"Name")
    IMPLEMENT_DATABASEATTRIBUTE(QString,Player,gender,"Gender")
    IMPLEMENT_DATABASEATTRIBUTE(int,Player,weight, "Weight")
    IMPLEMENT_DATABASEATTRIBUTE(int,Player,size, "Size")
    IMPLEMENT_DATABASEATTRIBUTE(QColor,Player,color, "Color")
    IMPLEMENT_DATABASEATTRIBUTE(QPixmap,Player,avatar, "Avatar")
    IMPLEMENT_DATABASEATTRIBUTE(int,Player,residence, "Residence")
}

QString Player::mimeType() const
{
    return "application/projectstats.player";
}

END_ROW_IMPLEMENTATION()
