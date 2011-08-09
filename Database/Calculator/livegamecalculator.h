#ifndef DATABASE_LIVEGAMECALCULATOR_H
#define DATABASE_LIVEGAMECALCULATOR_H

#include <QObject>
#include <QPointer>
#include <QPair>

#include <Database/round.h>

#include <Database/Calculator/gamecalculator.h>

class QTime;

namespace Database {

class LiveGame;
class LiveGameDrink;
class Player;
class Drink;

class LiveGameCalculator : public GameCalculator
{
    Q_OBJECT
public:
    explicit LiveGameCalculator(LiveGame* livegame, QObject *parent = 0);

    QList<Player*> calculate_playersSortedByPosition();

    QList<Player*> calculate_playersSortedByPlacement();

    QList<Player*> calculate_currentPlayingPlayers();

    QList<LiveGameDrink*> calculate_drinks();

    QMap<Drink*,int> calculate_drinkCount();

    QMap<Player*, QList<LiveGameDrink*> > calculate_drinksPerPlayer();

    virtual QMap<Player*,int> calculate_leadingRounds();

    virtual QMap<int,QMap<Player*,int> > calculate_placementAfterRounds();

    QList<Player*> calculate_playersSortedByAlcPegel();

    QList<Round*> calculate_rounds();

    QMap<Player*,int> calculate_points();

    QMap<Player*,int> calculate_placement();

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

bool sortPlayersByAlcPegel(QPair<Database::Player*,Database::LiveGame*> pair1, QPair<Database::Player*,Database::LiveGame*> pair2);

#endif // DATABASE_LIVEGAMECALCULATOR_H
