#include "dokolivegamegraphview.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Gui/Graphs/Items/dokolivegamecoordinatesystem.h>

using namespace Gui::Graphs;

DokoLiveGameGraphView::DokoLiveGameGraphView(QWidget *parent):
    LiveGameGraphView(parent)
{
}

void DokoLiveGameGraphView::setLiveGame(Database::LiveGame *liveGame)
{
    if(!m_liveGameCoordinateSystem.isNull())
    {
        scene()->removeItem(m_liveGameCoordinateSystem);
        m_liveGameCoordinateSystem->deleteLater();
    }

    m_liveGameCoordinateSystem = new Items::DokoLiveGameCoordinateSystem(static_cast<Database::DokoLiveGame*>(liveGame));
    m_liveGameCoordinateSystem->setParent(this);
    m_liveGameCoordinateSystem->setupSystem();
    connect(m_liveGameCoordinateSystem,SIGNAL(dimensionsChanged(QRectF)),this,SLOT(on_coordinateSystem_dimensionsChanged(QRectF)));


    scene()->addItem(m_liveGameCoordinateSystem);
    scene()->update();
}
