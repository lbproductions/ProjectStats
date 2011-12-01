#ifndef DATABASE_DOKOROUND_H
#define DATABASE_DOKOROUND_H

#include "../round.h"

#include <LBDatabase/LBDatabase.h>

namespace Database{
    class Schmeisserei;
    class DokoLiveGame;
    class DokoRoundCalculator;
}

START_ROW_DECLARATION(DokoRound, Round)
    DECLARE_ROW_CONSTRUCTORS(DokoRound, Round)

    DokoRound(DokoLiveGame* game, int number);

    DECLARE_DATABASEATTRIBUTE(int,DokoRound,doko_hochzeitPlayerId)
    DECLARE_DATABASEATTRIBUTE(int,DokoRound,doko_trumpfabgabePlayerId)
    DECLARE_DATABASEATTRIBUTE(int,DokoRound,doko_soloPlayerId)
    DECLARE_DATABASEATTRIBUTE(int,DokoRound,doko_schweinereiPlayerId)
    DECLARE_DATABASEATTRIBUTE(int,DokoRound,doko_re1PlayerId)
    DECLARE_DATABASEATTRIBUTE(int,DokoRound,doko_re2PlayerId)
    DECLARE_DATABASEATTRIBUTE(QString,DokoRound,doko_soloType)
    DECLARE_DATABASEATTRIBUTE(bool,DokoRound,doko_soloPflicht)

    DECLARE_LISTATTRIBUTE_IN_CALC(Schmeisserei*,DokoRound,DokoRoundCalculator,doko_schmeissereien)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,bool,DokoRound,DokoRoundCalculator,doko_re)

    void addSchmeisserei(Player* player, const QString& type);

END_ROW_DECLARATION(DokoRound)

#endif // DATABASE_DOKOROUND_H
