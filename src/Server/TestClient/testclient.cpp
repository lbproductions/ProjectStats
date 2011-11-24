#include "testclient.h"

TestClient::TestClient()
{
}

struct PlayerInformation TestClient::playerById(int id)
{
    projectstatsProxy psProxy;

    PlayerInformation playerInformation;
    psProxy.playerById("127.0.0.1:1332","urn:projectstats:playerById",id,playerInformation);

    return playerInformation;
}
