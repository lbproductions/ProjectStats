#include "dokoround.h"

#include "schmeisserei.h"
#include "dokolivegame.h"

#include <Database/database.h>
#include <Database/player.h>

START_ROW_IMPLEMENTATION(DokoRound, Round, Round)
{
    DokoRoundCalculator* calc = new DokoRoundCalculator(this);
    m_calc = calc;

    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_hochzeitPlayerId,tr("Doko_HochzeitPlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_trumpfabgabePlayerId,tr("Doko_TrumpfabgabePlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_soloPlayerId,tr("Doko_SoloPlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_schweinereiPlayerId,tr("Doko_SchweinereiPlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_re1PlayerId,tr("Doko_Re1PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,DokoRound,doko_re2PlayerId,tr("Doko_Re2PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,DokoRound,doko_soloType,tr("Doko_SoloType"))
    IMPLEMENT_DATABASEATTRIBUTE(bool,DokoRound,doko_soloPflicht,tr("Doko_SoloPflicht"))

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Schmeisserei*,DokoRound,DokoRoundCalculator,calc,doko_schmeissereien,tr("Schmeissereien"))

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,bool,DokoRound,DokoRoundCalculator,calc,doko_re,tr("Doko_Re"))

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Player*,DokoRound,DokoRoundCalculator,calc,doko_winningPlayers,tr("Doko_WinningPlayers"))

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(QList<Player*>,DokoRound,DokoRoundCalculator,calc,doko_togetherPlayingPlayers,tr("Doko_TogetherPlayingPlayers"))
}

DokoRound::DokoRound(DokoLiveGame* game, int number) :
    Round(game,number)
{
    initializeAttributes();
}

QString DokoRound::mimeType() const
{
    return "application/projectstats.dokoRound";
}

void DokoRound::addSchmeisserei(Player* player, const QString& type)
{
    Schmeisserei* schmeisserei = new Schmeisserei(player,this,type);
    addChildRow(schmeisserei);
    static_cast<DokoLiveGame*>(game->value())->doko_schmeisserei->recalculateFromScratch();
    this->doko_schmeissereien->recalculateFromScratch();
}

Player *DokoRound::rePlayer1() const
{
    return Players::instance()->rowById(doko_re1PlayerId->value()).data();
}

Player *DokoRound::rePlayer2() const
{
    return Players::instance()->rowById(doko_re2PlayerId->value()).data();
}

Player *DokoRound::schweinereiPlayer() const
{
    return Players::instance()->rowById(doko_schweinereiPlayerId->value()).data();
}

Player *DokoRound::hochzeitPlayer() const
{
    return Players::instance()->rowById(doko_hochzeitPlayerId->value()).data();
}

Player *DokoRound::dokoSoloPlayer() const
{
    return Players::instance()->rowById(doko_soloPlayerId->value()).data();
}

Player *DokoRound::trumpfabgabePlayer() const
{
    return Players::instance()->rowById(doko_trumpfabgabePlayerId->value()).data();
}

END_ROW_IMPLEMENTATION()
