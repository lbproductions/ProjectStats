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

class PlaceInformation
{
    int id;
    xsd__string name;
    int plz;
    xsd__string ort;
    xsd__string strasse;
    int number;
    xsd__string comment;
    int gameCount;
    std::vector<xsd__string> players;
};

class PlaceList
{
    std::vector<PlaceInformation> placeList;
};

class GameInformation
{
    int id;
    xsd__string name;
    xsd__string date;
    bool isLive;

    std::vector<PlayerInformation> playersSortedByPosition;
    std::vector<PlayerInformation> currentPlayingPlayers;
};

class GameList
{
    std::vector<GameInformation> gameList;
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

//gsoap ps service name: projectstats
//gsoap ps service port: http://eineurl.von.uns?
//gsoap ps service namespace: urn:projectstats

//gsoap ps service method-style: rpc
//gsoap ps service method-encoding: encoded
//gsoap ps service method-action: placeList ""
int ps__placeList(PlaceList& result);

//gsoap ps service name: projectstats
//gsoap ps service port: http://eineurl.von.uns?
//gsoap ps service namespace: urn:projectstats

//gsoap ps service method-style: rpc
//gsoap ps service method-encoding: encoded
//gsoap ps service method-action: gameList ""
int ps__gameList(GameList& result);

//gsoap ps service name: projectstats
//gsoap ps service port: http://eineurl.von.uns?
//gsoap ps service namespace: urn:projectstats

//gsoap ps service method-style: rpc
//gsoap ps service method-encoding: encoded
//gsoap ps service method-action: gameCurrentPlayingPlayers ""
int ps__gameCurrentPlayingPlayers(int gameId, PlayerList& result);

//gsoap ps service name: projectstats
//gsoap ps service port: http://eineurl.von.uns?
//gsoap ps service namespace: urn:projectstats

//gsoap ps service method-style: rpc
//gsoap ps service method-encoding: encoded
//gsoap ps service method-action: addSchmeisserei ""
int ps__addSchmeisserei(int gameId, int playerId, std::string type, std::string& result);

//gsoap ps service name: projectstats
//gsoap ps service port: http://eineurl.von.uns?
//gsoap ps service namespace: urn:projectstats

//gsoap ps service method-style: rpc
//gsoap ps service method-encoding: encoded
//gsoap ps service method-action: addDrink ""
int ps__addDrink(int gameId, int playerId, int drinkId, std::string& result);

#endif // SERVICEDESCRIPTION_H
