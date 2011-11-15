#include "server.h"

#include "stdsoap2.h"
#include "soapprojectstatsService.h"

#include <Database/player.h>
#include <Database/drink.h>
#include <Database/place.h>

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
        qDebug() << info.id << info.name;
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
