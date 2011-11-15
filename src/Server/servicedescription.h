#ifndef SERVICEDESCRIPTION_H
#define SERVICEDESCRIPTION_H

#import "stlvector.h"

typedef char* xsd__string; // encode xsd__string value as the xsd:string schema type

class StringIntPair
{
    xsd__string key;
    int value;
};

class StringDoublePair
{
    xsd__string key;
    double value;
};

class PlayerInformation
{
    int id;
    xsd__string name;
    std::vector<StringIntPair> games;
    std::vector<StringIntPair> wins;
    std::vector<StringIntPair> losses;
    std::vector<StringIntPair> points;
    std::vector<StringDoublePair> average;
};

class PlayerList
{
    std::vector<PlayerInformation> playerList;
};

class DrinkInformation
{
    int id;
    xsd__string name;
    xsd__string type;
    double size;
    double alc;
    int drinkCount;
    std::vector<StringIntPair> drinksPerPlayer;
};

class DrinkList
{
    std::vector<DrinkInformation> drinkList;
};

//gsoap ps service name: projectstats
//gsoap ps service port: http://eineurl.von.uns?
//gsoap ps service namespace: urn:projectstats

//gsoap ps service method-style: rpc
//gsoap ps service method-encoding: encoded
//gsoap ps service method-action: playerById ""
int ps__playerById(int id, PlayerInformation& result);

//gsoap ps service name: projectstats
//gsoap ps service port: http://eineurl.von.uns?
//gsoap ps service namespace: urn:projectstats

//gsoap ps service method-style: rpc
//gsoap ps service method-encoding: encoded
//gsoap ps service method-action: playerList ""
int ps__playerList(PlayerList& result);

//gsoap ps service name: projectstats
//gsoap ps service port: http://eineurl.von.uns?
//gsoap ps service namespace: urn:projectstats

//gsoap ps service method-style: rpc
//gsoap ps service method-encoding: encoded
//gsoap ps service method-action: drinkList ""
int ps__drinkList(DrinkList& result);

#endif // SERVICEDESCRIPTION_H
