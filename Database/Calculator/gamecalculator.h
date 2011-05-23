#ifndef DATABASE_GAMECALCULATOR_H
#define DATABASE_GAMECALCULATOR_H

#include <QObject>
#include <QPointer>
#include <QTime>

#include <Database/attributehash.h>
#include <Database/attributelist.h>

namespace Database {

class Game;
class Player;

class GameCalculator : public QObject
{
    Q_OBJECT
public:
    explicit GameCalculator(Game* game, QObject *parent = 0);

    AttributeList<Player*> calculate_players();

    virtual QTime calculate_length();

    virtual AttributeList<Player*> calculate_playersSortedByPosition();

    virtual AttributeHash<Player*,int> calculate_placement();

    virtual AttributeHash<Player*,int> calculate_points();

signals:

public slots:

protected:
    QPointer<Game> m_game;

};

} // namespace Database

#endif // DATABASE_GAMECALCULATOR_H
