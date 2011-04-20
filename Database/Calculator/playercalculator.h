#ifndef DATABASE_PLAYERCALCULATOR_H
#define DATABASE_PLAYERCALCULATOR_H

#include <QPointer>
#include <Database/attribute.h>

namespace Database {

class Player;
class Place;

class PlayerCalculator : public QObject
{
    Q_OBJECT
public:
    PlayerCalculator(QPointer<Player> player, QObject *parent = 0);

    int calculate_games();

    QList<Place*> calculate_places();

private:

    QPointer<Player> m_player;
};

} // namespace Database

#endif // DATABASE_PLAYERCALCULATOR_H
