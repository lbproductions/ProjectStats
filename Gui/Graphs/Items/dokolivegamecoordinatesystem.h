#ifndef DOKOLIVEGAMECOORDINATESYSTEM_H
#define DOKOLIVEGAMECOORDINATESYSTEM_H

#include "livegamecoordinatesystem.h"

namespace Database{
    class DokoLiveGame;
}

namespace Gui
{

namespace Graphs
{

namespace Items
{

class DokoLiveGameCoordinateSystem  : public LiveGameCoordinateSystem
{
    Q_OBJECT
public:
    DokoLiveGameCoordinateSystem(Database::DokoLiveGame* dokogame);

    void addGraphsForPlayers();
};

}}}

#endif // DOKOLIVEGAMECOORDINATESYSTEM_H
