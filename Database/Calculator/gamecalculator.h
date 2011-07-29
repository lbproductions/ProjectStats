#ifndef DATABASE_GAMECALCULATOR_H
#define DATABASE_GAMECALCULATOR_H

#include <QObject>
#include <QPointer>
#include <QTime>

#include <Database/round.h>

namespace Database {

class Game;
class Player;

class GameCalculator : public QObject
{
    Q_OBJECT
public:
    explicit GameCalculator(Game* game, QObject *parent = 0);

    QList<Player*> calculate_players();

    virtual QTime calculate_length();

    virtual QList<Player*> calculate_playersSortedByPosition();

    virtual QList<Player*> calculate_playersSortedByPlacement();

    virtual QMap<Player*,int> calculate_placement();

    virtual QMap<Player*,int> calculate_points();

    virtual int calculate_totalPoints();

    virtual Round::RoundState calculate_state();

signals:

public slots:

protected:
    QPointer<Game> m_game;

};

} // namespace Database

#endif // DATABASE_GAMECALCULATOR_H
