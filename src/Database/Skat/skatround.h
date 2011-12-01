#ifndef DATABASE_SKATROUND_H
#define DATABASE_SKATROUND_H

#include "../round.h"

#include <LBDatabase/LBDatabase.h>

START_ROW_DECLARATION(SkatRound, Round)
    DECLARE_ROW_CONSTRUCTORS(SkatRound, Round)

    DECLARE_DATABASEATTRIBUTE(int,SkatRound,skat_solistPlayerId)
    DECLARE_DATABASEATTRIBUTE(QString,SkatRound,skat_gameType)
    DECLARE_DATABASEATTRIBUTE(QString,SkatRound,skat_trumpfColor)


END_ROW_DECLARATION(SkatRound)

#endif // DATABASE_SKATROUND_H
