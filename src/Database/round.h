#ifndef DATABASE_ROUND_H
#define DATABASE_ROUND_H

#include "psrow.h"

#include <Database/Calculator/roundcalculator.h>

class QTimer;

namespace Database{
    class Game;
    class LiveGame;
}

namespace Database
{

template<class RowType>
class Table;

class Round : public PSRow
{
    Q_OBJECT

    DECLARE_ROW_CONSTRUCTORS(Round, Round)

    Round(Game* game, int number);

    enum RoundState {
        UnkownState, //!< Wenn das Attribut noch nicht initialisiert wurde
        RunningState, //!< Die Runde läuft gerade
        PausedState, //!< Die Runde ist Pausiert
        FinishedState //!< Die Runde wurde beendet
    };

    RoundCalculator* m_calc;

    DECLARE_DATABASEATTRIBUTE(int,Round,gameId)
    DECLARE_DATABASEATTRIBUTE(int,Round,number)
    DECLARE_DATABASEATTRIBUTE(QDateTime,Round,startTime)
    DECLARE_DATABASEATTRIBUTE(QTime,Round,length)
    DECLARE_DATABASEATTRIBUTE(int,Round,db_state)
    DECLARE_DATABASEATTRIBUTE(QString,Round,comment)

    DECLARE_ATTRIBUTE(LiveGame*,Round,game)
    DECLARE_ATTRIBUTE(RoundState,Round,state)

    OneToManyRelation<Round,Point>* points2;

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,Point*,Round,RoundCalculator,points)

    DECLARE_VIRTUAL_ATTRIBUTE_IN_CALC(int,Round,RoundCalculator,cardmixerPosition)
    DECLARE_VIRTUAL_LISTATTRIBUTE_IN_CALC(Player*,Round,RoundCalculator,currentPlayingPlayers)
    DECLARE_VIRTUAL_ATTRIBUTE_IN_CALC(int,Round,RoundCalculator,roundPoints)

    void setState(RoundState state);

    void addPoints(Player* player, int points);

private slots:
    void updateLength();

private:
    QTimer* m_timer;
};

}
Q_DECLARE_METATYPE(Database::Round)
Q_DECLARE_METATYPE(Database::Round*)
Q_DECLARE_METATYPE(QMap<Database::Round* COMMA int>)
Q_DECLARE_METATYPE(QList<Database::Round*>)
Q_DECLARE_METATYPE(QMap<int COMMA Database::Round*>)

Q_DECLARE_METATYPE(QMap<Database::Player* COMMA Database::Point*>)

START_TABLE_DECLARATION(Round)
    Round* createRowInstance(int id);
END_TABLE_DECLARATION()

Q_DECLARE_METATYPE(Database::Round::RoundState)

#endif // DATABASE_ROUND_H
