#ifndef DATABASE_LIVEGAMECALCULATOR_H
#define DATABASE_LIVEGAMECALCULATOR_H

#include <QObject>
#include <QPointer>
#include <QPair>

#include <Database/attributelist.h>
#include <Database/attributehash.h>
#include <Database/round.h>

#include <Database/Calculator/gamecalculator.h>

class QTime;

namespace Database {

class LiveGame;
class LiveGameDrink;
class Player;

class LiveGameCalculator : public GameCalculator
{
    Q_OBJECT
public:
    explicit LiveGameCalculator(LiveGame* livegame, QObject *parent = 0);

    AttributeList<Player*> calculate_playersSortedByPosition();

    AttributeList<Player*> calculate_playersSortedByPlacement();

    AttributeList<Player*> calculate_currentPlayingPlayers();

    AttributeList<LiveGameDrink*> calculate_drinks();

    AttributeHash<Player*, AttributeList<LiveGameDrink*> > calculate_drinksPerPlayer();

    AttributeList<Round*> calculate_rounds();

    AttributeHash<Player*,int> calculate_points();

    AttributeHash<Player*,int> calculate_placement();

    int calculate_roundCount();

    Round* calculate_lastRound();

    Round* calculate_currentRound();

    Round::RoundState calculate_state();

    Player* calculate_cardmixer();

    QTime calculate_length();

    int calculate_percComplete();

    virtual int calculate_totalPoints();

    bool calculate_isFinished();

signals:

public slots:

protected:
    QPointer<LiveGame> m_livegame;

};

} // namespace Database

bool sortPlayersByPosition(QPair<Database::Player*,Database::Game*> pair1, QPair<Database::Player*,Database::Game*> pair2);

bool sortPlayersByPlacement(QPair<Database::Player*,Database::Game*> pair1, QPair<Database::Player*,Database::Game*> pair2);

#endif // DATABASE_LIVEGAMECALCULATOR_H
