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

/*!
  Rundet die Zahl auf die angegebene Anzahl an Stellen.
  */
double round(double zahl, int stellen);

/*!
  Erstellt auf Basis eines Strings eine PlayerList.
  */
QList<Database::Player*> stringToPlayerList(QString string);
#endif // GLOBAL_H
