#ifndef PLAYERGRAPH_H
#define PLAYERGRAPH_H

#include <QPointer>
#include <Gui/Graphs/graphview.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>

class PlayerGraph : public Graph
{
public:
    PlayerGraph(Database::Player* player, Gui::Graphs::GraphView *view);

    void addRound(Database::Doppelkopf::DokoRound* round);

private:
    QList<Database::Doppelkopf::DokoRound> roundlist;

    Database::Player> m_player;
};

#endif // PLAYERGRAPH_H
