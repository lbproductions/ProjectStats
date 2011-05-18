#ifndef DATABASE_PLAYERCALCULATOR_H
#define DATABASE_PLAYERCALCULATOR_H

#include <QPointer>
#include <Database/attribute.h>
#include <Database/attributelist.h>

class QDateTime;

namespace Database {

class Player;
class Place;
class Game;

class PlayerCalculator : public QObject
{
    Q_OBJECT
public:
    PlayerCalculator(QPointer<Player> player, QObject *parent = 0);

    AttributeList<Game*> calculate_games();

    int calculate_points();

    AttributeList<Place*> calculate_places();

    double calculate_average();

    int calculate_wins();

    int calculate_losses();

    QDateTime calculate_lastGame();

    QDateTime calculate_lastWin();

private:

    QPointer<Player> m_player;
};

} // namespace Database

#endif // DATABASE_PLAYERCALCULATOR_H
