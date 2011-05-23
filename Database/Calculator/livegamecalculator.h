#ifndef DATABASE_LIVEGAMECALCULATOR_H
#define DATABASE_LIVEGAMECALCULATOR_H

#include <QObject>
#include <QPointer>
#include <QPair>

#include <Database/attributelist.h>
#include <Database/attributehash.h>

#include <Database/Calculator/gamecalculator.h>

class QTime;

namespace Database {

class LiveGame;
class Drink;
class Round;
class Player;

class LiveGameCalculator : public GameCalculator
{
    Q_OBJECT
public:
    explicit LiveGameCalculator(LiveGame* livegame, QObject *parent = 0);

    AttributeList<Player*> calculate_playersSortedByPosition();

    AttributeList<Drink*> calculate_drinks();

    AttributeList<Round*> calculate_rounds();

    AttributeHash<Player*,int> calculate_points();

    QTime calculate_length();

    AttributeHash<Player*,int> calculate_placement();

    int calculate_percComplete();


signals:

public slots:

private:
    QPointer<LiveGame> m_livegame;

};

} // namespace Database

bool sortPlayersByPosition(QPair<Database::Player*,Database::Game*> pair1, QPair<Database::Player*,Database::Game*> pair2);

#endif // DATABASE_LIVEGAMECALCULATOR_H
