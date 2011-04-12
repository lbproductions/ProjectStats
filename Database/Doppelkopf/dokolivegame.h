#ifndef DATABASE_DOKOLIVEGAME_H
#define DATABASE_DOKOLIVEGAME_H

#include "../livegame.h"

#include "../row.h"
#include "../table.h"
#include "../databaseattribute.h"

START_ROW_DECLARATION(DokoLiveGame, LiveGame)
    DECLARE_ROW_CONSTRUCTORS(DokoLiveGame, Game)

    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,mitHochzeit)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,mitSolo)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,mitTrumpfabgabe)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,mitSchweinerei)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,mitSchmeisserei)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,mitPflichtsolo)

END_ROW_DECLARATION(DokoLiveGame)

#endif // DATABASE_DOPPELKOPF_DOKOLIVEGAME_H
