#ifndef DATABASE_GAMECALCULATOR_H
#define DATABASE_GAMECALCULATOR_H

#include <QObject>
#include <QPointer>

namespace Database {

class Game;
class Player;

class GameCalculator : public QObject
{    
    Q_OBJECT
public:
    explicit GameCalculator(Game* game, QObject *parent = 0);

    QList<Player*> calculate_players();

signals:

public slots:

private:
    QPointer<Game> m_game;

};

} // namespace Database

#endif // DATABASE_GAMECALCULATOR_H
