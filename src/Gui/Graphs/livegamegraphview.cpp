#include "livegamegraphview.h"

#include "Items/livegamecoordinatesystem.h"

#include <Database/livegame.h>
#include <Database/player.h>

using namespace Gui::Graphs;

LiveGameGraphView::LiveGameGraphView(QWidget *parent) :
    GraphView(parent)
{
}

void LiveGameGraphView::setupView(Database::LiveGame *liveGame){
    setLiveGame(liveGame);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void LiveGameGraphView::setLiveGame(Database::LiveGame *liveGame)
{
    if(!m_liveGameCoordinateSystem.isNull())
    {
	scene()->removeItem(m_liveGameCoordinateSystem);
	m_liveGameCoordinateSystem->deleteLater();
    }

    m_liveGameCoordinateSystem = new Items::LiveGameCoordinateSystem(liveGame);
    m_liveGameCoordinateSystem->setupSystem();
    connect(m_liveGameCoordinateSystem,SIGNAL(dimensionsChanged(QRectF)),this,SLOT(on_coordinateSystem_dimensionsChanged(QRectF)));
    scene()->addItem(m_liveGameCoordinateSystem);
    scene()->update();
}

void LiveGameGraphView::on_coordinateSystem_dimensionsChanged(QRectF)
{
    resizeEvent(0);
}

void LiveGameGraphView::resizeEvent(QResizeEvent * /*event*/)
{
    m_liveGameCoordinateSystem->updateScales(this->height(),this->width());
    centerOn(m_liveGameCoordinateSystem);
    setSceneRect(m_liveGameCoordinateSystem->boundingRect());
}
