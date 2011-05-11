#ifndef DATABASE_GAMECALCULATOR_H
#define DATABASE_GAMECALCULATOR_H

#include <QObject>
#include <QPointer>

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

    AttributeList<Player*>* calculate_players();

    AttributeHash<Player*,int>* calculate_placement();

signals:

public slots:

private:
    QPointer<Game> m_game;

};

} // namespace Database

#endif // DATABASE_GAMECALCULATOR_H
