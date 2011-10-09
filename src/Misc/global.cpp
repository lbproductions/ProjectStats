#include "global.h"

#include <QTime>
#include <Database/player.h>
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
