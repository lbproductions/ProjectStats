#include "graphview.h"

using namespace Gui::Graphs;

GraphView::GraphView(QWidget *parent) :
    QGraphicsView(parent)
{
    setScene(new QGraphicsScene(this));
    setRenderHints(renderHints() | QPainter::Antialiasing | QPainter::TextAntialiasing);
}
