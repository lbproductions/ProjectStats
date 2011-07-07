#ifndef DOKOLIVEGAMEPLAYERPOINTSGRAPH_H
#define DOKOLIVEGAMEPLAYERPOINTSGRAPH_H

#include <Gui/Graphs/Items/livegameplayerpointsgraph.h>

namespace Database
{

class Player;

class DokoLiveGame;
class DokoRound;
}

namespace Gui
{

namespace Graphs
{

namespace Items
{

class LiveGameCoordinateSystem;

class DokoLiveGamePlayerPointsGraph : public LiveGamePlayerPointsGraph
{
    Q_OBJECT
public:
    DokoLiveGamePlayerPointsGraph(Database::Player *player, Database::DokoLiveGame *liveGame, LiveGameCoordinateSystem *coordinateSystem);

    void addPoint(const QPoint &point, ::Database::DokoRound* r);

public slots:

    void addRound(::Database::Round*);
};

}}}

#endif // DOKOLIVEGAMEPLAYERPOINTSGRAPH_H
