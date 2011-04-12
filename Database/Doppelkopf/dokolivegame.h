#ifndef DATABASE_DOKOLIVEGAME_H
#define DATABASE_DOKOLIVEGAME_H

#include "../livegame.h"

#include "../row.h"
#include "../table.h"
#include "../databaseattribute.h"

START_ROW_DECLARATION(DokoLiveGame, LiveGame)
    DECLARE_ROW_CONSTRUCTORS(DokoLiveGame, Game)

    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitHochzeit)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSolo)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitTrumpfabgabe)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchweinerei)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchmeisserei)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitPflichtsolo)

END_ROW_DECLARATION(DokoLiveGame)

#endif // DATABASE_DOPPELKOPF_DOKOLIVEGAME_H
