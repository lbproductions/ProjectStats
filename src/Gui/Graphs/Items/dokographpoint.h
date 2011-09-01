#ifndef DOKOGRAPHPOINT_H
#define DOKOGRAPHPOINT_H

#include "graphpoint.h"

namespace Database{
    class Player;
    class DokoRound;
}

namespace Gui
{

namespace Graphs
{

namespace Items
{

class DokoLiveGamePlayerPointsGraph;

class DokoGraphPoint : public GraphPoint
{
    Q_OBJECT
public:
    DokoGraphPoint(QPoint point, DokoLiveGamePlayerPointsGraph* graph, ::Database::DokoRound* r);

    /*!
      Zeichnet den Punkt.
      */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    Database::DokoRound* round() const;
private:

    Database::DokoRound* m_dokoround;
    Database::Player* m_player;
};

}}}

#endif // DOKOGRAPHPOINT_H
