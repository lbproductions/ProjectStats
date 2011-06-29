#ifndef GLOBAL_H
#define GLOBAL_H

#include <QApplication>

class QTime;

namespace Database{
    class Player;
}

/*!
  Addiert zwei Zeiten.
  */
QTime operator+(const QTime &time1, const QTime &time2);

#endif // GLOBAL_H
