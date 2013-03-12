#ifndef GLOBAL_H
#define GLOBAL_H

#include <QApplication>

class QTime;

namespace Database{
    class Player;
    class RowPair;
    bool qMapLessThanKey(const RowPair &key1, const RowPair &key2);
    bool operator<(const RowPair &e1, const RowPair &e2);
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


bool operator==(const Database::RowPair &e1, const Database::RowPair &e2);

QDebug operator<<(QDebug d, const QList<Database::RowPair> list);

QDebug operator<<(QDebug d, const Database::RowPair pair);

#endif // GLOBAL_H
