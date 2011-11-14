#include "server.h"

#include "stdsoap2.h"
#include "soapprojectstatsService.h"

#include <Database/player.h>

#include <QDebug>

Server::Server(QObject *parent) :
    QThread(parent)
{
}

void Server::run()
{
    projectstatsService psService;
    psService.bind("127.0.0.1",1332,100);

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
