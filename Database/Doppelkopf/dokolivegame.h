#ifndef DATABASE_DOKOLIVEGAME_H
#define DATABASE_DOKOLIVEGAME_H

#include "../livegame.h"

#include "../row.h"
#include "../table.h"
#include "../databaseattribute.h"

#include <Database/mappingattribute.h>
#include <Database/Calculator/dokolivegamecalculator.h>

START_ROW_DECLARATION(DokoLiveGame, LiveGame)
    DECLARE_ROW_CONSTRUCTORS(DokoLiveGame, Game)

    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitHochzeit)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSolo)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitTrumpfabgabe)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchweinerei)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchmeisserei)
    DECLARE_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitPflichtsolo)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_re)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_reWins)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_contra)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_contraWins)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_hochzeit)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_solo)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_trumpfabgabe)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_schweinerei)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,doko_schmeisserei)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,bool,DokoLiveGame,DokoLiveGameCalculator,doko_hasPflichtSolo)

    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_hochzeitCount)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_soloCount)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_pflichtSoloCount)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_trumpfabgabeCount)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_schweinereiCount)
    DECLARE_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,doko_schmeissereiCount)

END_ROW_DECLARATION(DokoLiveGame)

#endif // DATABASE_DOPPELKOPF_DOKOLIVEGAME_H
