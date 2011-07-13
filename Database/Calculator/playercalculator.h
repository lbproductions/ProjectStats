#ifndef DATABASE_PLAYERCALCULATOR_H
#define DATABASE_PLAYERCALCULATOR_H

#include <QPointer>
#include <Database/attribute.h>
#include <Database/attributelist.h>
#include <Database/attributehash.h>

class QDateTime;

namespace Gui{
    namespace Details{
        class AbstractPlayerStatsWidget;
    }
}

namespace Database {

class Player;
class Place;
class Game;
class LiveGame;

class PlayerCalculator : public QObject
{
    Q_OBJECT
public:
    PlayerCalculator(QPointer<Player> player, QObject *parent = 0);

    AttributeList<Game*> calculate_games();

    AttributeHash<QString,int> calculate_points();

    AttributeList<Place*> calculate_places();

    AttributeHash<QString,double> calculate_average();

    AttributeHash<QString,int> calculate_wins();

    AttributeHash<QString,int> calculate_losses();

    AttributeHash<QString,int> calculate_gameCount();

    QDateTime calculate_lastGame();

    QDateTime calculate_lastWin();

    AttributeHash<LiveGame*,double> calculate_alcPegel();

private:

    QPointer<Player> m_player;
};

} // namespace Database

#endif // DATABASE_PLAYERCALCULATOR_H
