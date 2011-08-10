#include "graphview.h"

using namespace Gui::Graphs;

GraphView::GraphView(QWidget *parent) :
    QGraphicsView(parent),
    m_isFullscreen(false)
{
    setScene(new QGraphicsScene(this));
    setRenderHints(renderHints() | QPainter::Antialiasing | QPainter::TextAntialiasing);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void GraphView::setFullscreen(){
    this->setStyleSheet("QWidget{background-color:black; color:white; border-radius: 10px; margin-bottom: 10px; border:1px solid black;}");
    m_isFullscreen = true;
}

void GraphView::setNormalMode(){
    this->setStyleSheet("");
    m_isFullscreen = false;
}

bool GraphView::isFullscreen() const
{
    return m_isFullscreen;
}
