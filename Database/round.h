#ifndef DATABASE_ROUND_H
#define DATABASE_ROUND_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"
#include "mappingattribute.h"
#include "listattribute.h"

#include <Database/Calculator/roundcalculator.h>

namespace Database{
    class Game;
}

START_ROW_DECLARATION(Round, Row)
    DECLARE_ROW_CONSTRUCTORS(Round, Round)

    Round(Game* game, int number);

    enum RoundState {
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

    DECLARE_ATTRIBUTE(QPointer<Game>,Round,game)
    DECLARE_ATTRIBUTE(RoundState,Round,state)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Round,RoundCalculator,points)

    DECLARE_VIRTUAL_ATTRIBUTE_IN_CALC(int,Round,RoundCalculator,cardmixerPosition)
    DECLARE_VIRTUAL_LISTATTRIBUTE_IN_CALC(Player*,Round,RoundCalculator,currentPlayingPlayers)
    DECLARE_VIRTUAL_ATTRIBUTE_IN_CALC(int,Round,RoundCalculator,roundPoints)

END_ROW_DECLARATION(Round)

START_TABLE_DECLARATION(Round)
QPointer<Round> createRowInstance(int id);
END_TABLE_DECLARATION()

Q_DECLARE_METATYPE(Database::Round::RoundState)

#endif // DATABASE_ROUND_H
