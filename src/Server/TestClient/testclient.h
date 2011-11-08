#ifndef TESTCLIENT_H
#define TESTCLIENT_H

#include "../soapprojectstatsProxy.h"

class TestClient
{
public:
    TestClient();

    PlayerInformation playerById(int id);
};

#endif // TESTCLIENT_H
