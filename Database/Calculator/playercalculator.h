#ifndef DATABASE_PLAYERCALCULATOR_H
#define DATABASE_PLAYERCALCULATOR_H

#include <QPointer>
#include <Database/attribute.h>
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

    QList<Game*> calculate_games();

    QMap<QString,int> calculate_points();

    QList<Place*> calculate_places();

    QMap<QString,double> calculate_average();

    QMap<QString,int> calculate_wins();

    QMap<QString,int> calculate_losses();

    QMap<QString,int> calculate_gameCount();

    QMap<QString,QDateTime> calculate_lastGame();

    QMap<QString,QDateTime> calculate_lastWin();

    QMap<LiveGame*,double> calculate_alcPegel();

    QMap<QString,double> calculate_averagePlacement();

    double calculate_liveAverage();

private:

    QPointer<Player> m_player;
};

} // namespace Database

#endif // DATABASE_PLAYERCALCULATOR_H
