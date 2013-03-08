#include "global.h"

#include <QTime>
#include <Database/player.h>
#include <Database/rowpair.h>
#include <math.h>

QTime operator+(const QTime &time1, const QTime &time2)
{
    int secs = time1.second() + time2.second();
    int mins = 0;
    if (secs > 59){
	mins = secs/60;
	secs = secs%60;
    }
    mins = mins + time1.minute() + time2.minute();
    int hours = 0;
    if (mins > 59){
	hours = mins/60;
	mins = mins%60;
    }
    hours = hours + time1.hour() + time2.hour();
    return QTime(hours,mins,secs);
}

double round(double zahl, int stellen)
{
    double v[] = { 1, 10, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8 };  // mgl. verlängern
    return floor(zahl * v[stellen] + 0.5) / v[stellen];
}

QList<Database::Player*> stringToPlayerList(QString string)
{
    QList<Database::Player*> players;

    QList<QString> strings = string.split(", ");
    foreach(QString name, strings)
    {
        players.append(Database::Players::instance()->playerByName(name));
    }

    return players;
}

bool operator<(const Database::RowPair &e1, const Database::RowPair &e2)
{
    return e1.first()->id() < e2.first()->id();
}

bool operator==(const Database::RowPair &e1, const Database::RowPair &e2)
{
    if((e1.first()->id() == e2.first()->id() && e1.second()->id() == e2.second()->id()) || (e1.first()->id() == e2.second()->id() && e1.second()->id() == e2.first()->id()))
    {
        return true;
    }
    return false;
}

QDebug operator<<(QDebug d, const QList<Database::RowPair> list)
{
    foreach(Database::RowPair pair, list){
        d << pair.first()->id() << " - " << pair.second()->id() << ", ";
    }
    return d;
}

QDebug operator<<(QDebug d, const Database::RowPair pair)
{
    d << pair.first()->id() << " - " << pair.second()->id();
    return d;
}

