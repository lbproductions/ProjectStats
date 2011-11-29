#include "server.h"

#include "stdsoap2.h"
#include "soapprojectstatsService.h"

#include <Database/player.h>
#include <Database/drink.h>
#include <Database/place.h>
#include <Database/game.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>

#include <QDebug>

Server::Server(QObject *parent) :
    QThread(parent)
{
}

void Server::run()
{
    projectstatsService psService;
    psService.bind(NULL,1332,100);

    int s;
    for (int i = 1; ; i++)
    {
        s = psService.accept();
        if (s < 0)
        {
            psService.soap_print_fault(stderr);
            break;
        }
        //qDebug() << "Server::run: accepted" << i << ". connection from IP " << ((psService.soap->ip >> 24)&0xFF) << "." << ((psService.soap->ip >> 16)&0xFF) << "." << ((psService.soap->ip >> 8)&0xFF) << "." << (psService.soap->ip&0xFF) << "; socket =" << s;

        if (psService.serve() != SOAP_OK) // process RPC request
            psService.soap_print_fault(stderr);
        qDebug() << "request served";
    }
    psService.destroy(); // clean up class instances
}

int projectstatsService::playerById(int id, PlayerInformation &result)
{
    Database::Player* player = Database::Players::instance()->rowById(id);

    if(!player)
    {
        return SOAP_USER_ERROR;
    }

    result.name = player->name->value().toUtf8().data();
    result.id = id;

    return SOAP_OK;
}

int projectstatsService::playerList(PlayerList& result)
{
    foreach(Database::Player* player, Database::Players::instance()->allRows())
    {
        PlayerInformation info;
        QByteArray ba = player->name->value().toLocal8Bit();
        info.name = strdup(ba.data());
        info.id = player->id();
        foreach(QString type ,player->gameCount->value().keys()){
            StringIntPair pair;
            QByteArray ba = type.toLocal8Bit();
            pair.key = strdup(ba.data());
            pair.value = player->gameCount->value(type);
            info.games.push_back(pair);
        }
        foreach(QString type ,player->wins->value().keys()){
            StringIntPair pair;
            QByteArray ba = type.toLocal8Bit();
            pair.key = strdup(ba.data());
            pair.value = player->wins->value(type);
            info.wins.push_back(pair);
        }
        foreach(QString type ,player->losses->value().keys()){
            StringIntPair pair;
            QByteArray ba = type.toLocal8Bit();
            pair.key = strdup(ba.data());
            pair.value = player->losses->value(type);
            info.losses.push_back(pair);
        }
        foreach(QString type ,player->points->value().keys()){
            StringIntPair pair;
            QByteArray ba = type.toLocal8Bit();
            pair.key = strdup(ba.data());
            pair.value = player->points->value(type);
            info.points.push_back(pair);
        }
        foreach(QString type ,player->average->value().keys()){
            StringDoublePair pair;
            QByteArray ba = type.toLocal8Bit();
            pair.key = strdup(ba.data());
            pair.value = player->average->value(type);
            info.average.push_back(pair);
        }
        result.playerList.push_back(info);
    }

    return SOAP_OK;
}

int projectstatsService::drinkList(DrinkList& result)
{
    foreach(Database::Drink* drink, Database::Drinks::instance()->allRows())
    {
        DrinkInformation info;
        QByteArray ba = drink->name->value().toLocal8Bit();
        info.name = strdup(ba.data());
        info.id = drink->id();
        QByteArray ty = drink->type->value().toLocal8Bit();
        info.type = strdup(ty.data());
        info.alc = drink->alc->value();
        info.size = drink->size->value();
        info.drinkCount = drink->drinkCount->value();
        foreach(Database::Player* player ,drink->countPerPlayer->value().keys()){
            StringIntPair pair;
            QByteArray ba = player->name->value().toLocal8Bit();
            pair.key = strdup(ba.data());
            pair.value = drink->countPerPlayer->value(player);
            info.drinksPerPlayer.push_back(pair);
        }
        result.drinkList.push_back(info);
    }
    return SOAP_OK;
}

int projectstatsService::placeList(PlaceList& result)
{
    foreach(Database::Place* place, Database::Places::instance()->allRows())
    {
        PlaceInformation info;
        QByteArray ba = place->displayString->value().toLocal8Bit();
        info.name = strdup(ba.data());
        info.id = place->id();
        QByteArray ty = place->strasse->value().toLocal8Bit();
        info.strasse = strdup(ty.data());
        info.number = place->nummer->value();
        info.plz = place->plz->value();
        info.gameCount = place->gameCount->value();
        QByteArray com = place->comment->value().toLocal8Bit();
        info.comment = strdup(com.data());
        QByteArray ort = place->ort->value().toLocal8Bit();
        info.ort = strdup(ort.data());
        foreach(Database::Player* player ,place->players->value()){
            QByteArray ba = player->name->value().toLocal8Bit();
            info.players.push_back(strdup(ba.data()));
        }
        result.placeList.push_back(info);
    }
    return SOAP_OK;
}

int projectstatsService::gameList(GameList& result)
{
    foreach(Database::Game* game, Database::Games::instance()->allRows())
    {
        GameInformation info;
        QByteArray ba = game->name->value().toLocal8Bit();
        info.name = strdup(ba.data());
        info.id = game->id();
        info.isLive = game->live->value();
        ba = game->date->value().toString("dd.MM.yyyy").toLocal8Bit();
        info.date = strdup(ba.data());

        if(game->live->value()){
            Database::LiveGame* liveGame = static_cast<Database::LiveGame*>(game);
            foreach(Database::Player* player, liveGame->playersSortedByPosition->value()){
                PlayerInformation playerInfo;
                QByteArray ba = player->name->value().toLocal8Bit();
                playerInfo.name = strdup(ba.data());
                playerInfo.id = player->id();
                info.playersSortedByPosition.push_back(playerInfo);
            }
            foreach(Database::Player* player, liveGame->currentPlayingPlayers->value()){
                PlayerInformation playerInfo;
                QByteArray ba = player->name->value().toLocal8Bit();
                playerInfo.name = strdup(ba.data());
                playerInfo.id = player->id();
                info.currentPlayingPlayers.push_back(playerInfo);
            }
        }
        result.gameList.push_back(info);
    }
    return SOAP_OK;
}

int projectstatsService::gameCurrentPlayingPlayers(int gameId, PlayerList& result)
{
    Database::LiveGame* game = static_cast<Database::LiveGame*>(Database::Games::instance()->rowById(gameId));
    foreach(Database::Player* player, game->currentPlayingPlayers->value())
    {
        PlayerInformation info;
        QByteArray ba = player->name->value().toLocal8Bit();
        info.name = strdup(ba.data());
        info.id = player->id();

        result.playerList.push_back(info);
    }

    return SOAP_OK;
}

int projectstatsService::addSchmeisserei(int gameId, int playerId, std::string type, std::string& /*result*/)
{
    Database::Game* game = Database::Games::instance()->rowById(gameId);

    if(game->live->value() && game->type->value() == "Doppelkopf")
    {
        Database::DokoLiveGame* dokogame = static_cast<Database::DokoLiveGame*>(game);

        if(!dokogame->isFinished->value())
        {
            Database::DokoRound* round = static_cast<Database::DokoRound*>(dokogame->currentRound->value());
            Database::Player* player = Database::Players::instance()->rowById(playerId);
            QString stype = QString::fromUtf8(type.c_str());
            round->addSchmeisserei(player, stype);
        }
    }

    return SOAP_OK;
}

int projectstatsService::addDrink(int gameId, int playerId, int drinkId, std::string& /*result*/)
{
    Database::Game* game = Database::Games::instance()->rowById(gameId);

    if(game->live->value()){
        Database::LiveGame* liveGame = static_cast<Database::LiveGame*>(game);
        Database::Drink* drink = Database::Drinks::instance()->rowById(drinkId);
        Database::Player* player = Database::Players::instance()->rowById(playerId);
        liveGame->addDrink(player,drink);
    }

    return SOAP_OK;
}

int projectstatsService::addRound(int gameId, int re1PlayerId, int re2PlayerId, int hochzeitPlayerId, int schweinereiPlayerId, int trumpfabgabePlayerId, std::string soloType, bool pflichtsolo, int points, std::string comment, std::string &/*result*/)
{
    Database::Game* game = Database::Games::instance()->rowById(gameId);

    if(game->live->value() && game->type->value() == "Doppelkopf")
    {
        Database::DokoLiveGame* dokogame = static_cast<Database::DokoLiveGame*>(game);

        if(!dokogame->isFinished->value())
        {
            Database::DokoRound* round = static_cast<Database::DokoRound*>(dokogame->currentRound->value());

            // Kein Solo
            if (soloType == "")
            {
                Database::Player* re1 = Database::Players::instance()->rowById(re1PlayerId);
                Database::Player* re2 = Database::Players::instance()->rowById(re2PlayerId);

                Database::Player* contra1 = 0;
                Database::Player* contra2 = 0;

                int contraCount = 0;
                foreach(Database::Player* player, dokogame->currentPlayingPlayers->value())
                {
                    if (player->id() != re1->id() && player->id() != re2->id())
                    {
                        if (contraCount == 0)
                        {
                            contra1 = player;
                        }
                        if (contraCount == 1)
                        {
                            contra2 = player;
                        }
                        contraCount++;
                    }
                }

                round->doko_re1PlayerId->setValue(re1PlayerId);
                round->doko_re2PlayerId->setValue(re2PlayerId);

                round->addPoints(re1,points);
                round->addPoints(re2,points);
                round->addPoints(contra1,-points);
                round->addPoints(contra2,-points);

                if (hochzeitPlayerId > 0)
                {
                    round->doko_hochzeitPlayerId->setValue(hochzeitPlayerId);
                }
                if (schweinereiPlayerId > 0)
                {
                    round->doko_schweinereiPlayerId->setValue(schweinereiPlayerId);
                }
                if (trumpfabgabePlayerId > 0)
                {
                    round->doko_trumpfabgabePlayerId->setValue(trumpfabgabePlayerId);
                }
            }
            // Solo
            else
            {
                Database::Player* re1 = Database::Players::instance()->rowById(re1PlayerId);
                Database::Player* contra1 = 0;
                Database::Player* contra2 = 0;
                Database::Player* contra3 = 0;

                int contraCount = 0;
                foreach(Database::Player *player, dokogame->currentPlayingPlayers->value())
                {
                    if (player->id() != re1->id())
                    {
                        if (contraCount == 0)
                        {
                            contra1 = player;
                        }
                        if (contraCount == 1)
                        {
                            contra2 = player;
                        }
                        if (contraCount == 2)
                        {
                            contra3 = player;
                        }
                        contraCount++;
                    }
                }

                round->doko_re1PlayerId->setValue(re1PlayerId);
                round->doko_soloPlayerId->setValue(re1PlayerId);
                round->doko_soloType->setValue(QString::fromStdString(soloType));
                round->doko_soloPflicht->setValue(pflichtsolo);

                round->addPoints(re1,3*points);
                round->addPoints(contra1,-points);
                round->addPoints(contra2,-points);
                round->addPoints(contra3,-points);
            }
            round->comment->setValue(QString::fromStdString(comment));
            dokogame->startNextRound();
            dokogame->currentRound->value()->startTime->setValue(QDateTime().currentDateTime());
        }
    }
    return SOAP_OK;
}
