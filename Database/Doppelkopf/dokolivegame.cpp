#include "dokolivegame.h"


START_ROW_IMPLEMENTATION(DokoLiveGame, Game, LiveGame)
{
    DokoLiveGameCalculator* calc = new DokoLiveGameCalculator(this);
    m_calc = calc;

    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitHochzeit,tr("Doko_MitHochzeit"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSolo,tr("Doko_MitSolo"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitTrumpfabgabe,tr("Doko_MitTrumpfabgabe"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchweinerei,tr("Doko_MitSchweinerei"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitSchmeisserei,tr("Doko_MitSchmeisserei"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoLiveGame,doko_mitPflichtsolo,tr("Doko_MitPflichtsolo"))

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_re,"Doko_Re")
    rounds->addDependingAttribute(doko_re);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_reWins,"Doko_Re_Wins")
    doko_re->addDependingAttribute(doko_reWins);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_contra,"Doko_Contra")
    rounds->addDependingAttribute(doko_contra);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_contraWins,"Doko_Contra_Wins")
    doko_contra->addDependingAttribute(doko_contraWins);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_hochzeit,tr("Doko_Hochzeit"))
    rounds->addDependingAttribute(doko_hochzeit);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_solo,tr("Doko_Solo"))
    rounds->addDependingAttribute(doko_solo);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_trumpfabgabe,tr("Doko_Trumpfabgabe"))
    rounds->addDependingAttribute(doko_trumpfabgabe);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schweinerei,tr("Doko_Schweinerei"))
    rounds->addDependingAttribute(doko_schweinerei);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schmeisserei,tr("Doko_Schmeisserei"))
    rounds->addDependingAttribute(doko_schmeisserei);
    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,bool,DokoLiveGame,DokoLiveGameCalculator,calc,doko_hasPflichtSolo,tr("Doko_HasPflichtsolo"))
    rounds->addDependingAttribute(doko_hasPflichtSolo);

    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_hochzeitCount,tr("Doko_HochzeitCount"))
    doko_hochzeit->addDependingAttribute(doko_hochzeitCount);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_soloCount,tr("Doko_SoloCount"))
    doko_solo->addDependingAttribute(doko_soloCount);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_pflichtSoloCount,tr("Doko_PflichtSoloCount"))
    doko_hasPflichtSolo->addDependingAttribute(doko_pflichtSoloCount);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_trumpfabgabeCount,tr("Doko_TrumpfabgabenCount"))
    doko_trumpfabgabe->addDependingAttribute(doko_trumpfabgabeCount);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schweinereiCount,tr("Doko_SchweinereienCount"))
    doko_schweinerei->addDependingAttribute(doko_schweinereiCount);
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,DokoLiveGame,DokoLiveGameCalculator,calc,doko_schmeissereiCount,tr("Doko_SchmeissereienCount"))
    doko_schmeisserei->addDependingAttribute(doko_schmeissereiCount);

}

QString DokoLiveGame::mimeType() const
{
    return "application/projectstats.dokoLiveGame";
}

END_ROW_IMPLEMENTATION()
