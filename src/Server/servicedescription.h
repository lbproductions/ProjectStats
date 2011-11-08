#ifndef SERVICEDESCRIPTION_H
#define SERVICEDESCRIPTION_H

typedef char* xsd__string; // encode xsd__string value as the xsd:string schema type
class PlayerInformation
{
    xsd__string name;
};

//gsoap ps service name: projectstats
//gsoap ps service port: http://eineurl.von.uns?
//gsoap ps service namespace: urn:projectstats

//gsoap ps service method-style: rpc
//gsoap ps service method-encoding: encoded
//gsoap ps service method-action: playerById ""
int ps__playerById(int id, PlayerInformation& result);

#endif // SERVICEDESCRIPTION_H
