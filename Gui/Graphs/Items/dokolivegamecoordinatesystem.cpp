#include "dokolivegamecoordinatesystem.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/player.h>

#include "dokolivegameplayerpointsgraph.h"

using namespace Gui::Graphs::Items;

DokoLiveGameCoordinateSystem::DokoLiveGameCoordinateSystem(Database::DokoLiveGame* dokogame):
    LiveGameCoordinateSystem(dokogame)
{
}

void DokoLiveGameCoordinateSystem::addGraphsForPlayers()
{
    foreach(Database::Player *player, m_liveGame->playersSortedByPosition->value())
    {
        DokoLiveGamePlayerPointsGraph* graph = new DokoLiveGamePlayerPointsGraph(player,static_cast<Database::DokoLiveGame*>(m_liveGame),this);
        graph->setupGraph();
        addGraph(graph);
    }
}
