#ifndef LIVEGAMEGRAPHVIEW_H
#define LIVEGAMEGRAPHVIEW_H

#include "graphview.h"

#include <QPointer>

namespace Database
{
class LiveGame;
class Player;
}

namespace Gui
{
namespace Graphs
{

namespace Items
{
class LiveGameCoordinateSystem;
}

//! Zeigt die Punkteverläufe von einem LiveGame an.
/*!
  Für jeden Spieler wird dafür ein eigener Graph erstellt, der für jede Runde die bis dahin erreichte Punktzahl anzeigt.<br>
  Das LiveGame kann entweder direkt an den Konstruktor übergeben werden oder später mit setLiveGame() gesetzt werden.<br>
  Änderungen am Spiel, wie eine neue abgeschlossene Runde beachtet jeder Graph für sich.<br>
  Diese Klasse hier verwaltet dabei nur ein LiveGameCoordinateSystem, welches sich um je einen LiveGamePlayerPointsGraph pro Spieler kümmert.<br>
  Größenänderungen am View werden dem Koordinatensystem per CoordinateSystem::updateScales() mitgeteilt, welches dann seine Skalierung anpasst, sodass alle Graphen wieder in den View passen und diesen komplett ausfüllen.
  */
class LiveGameGraphView : public GraphView
{
    Q_OBJECT
public:
    /*!
      Erstellt einen LiveGameGraphView, der das LiveGame \p liveGame verfolgt und anzeigt.
      */
    LiveGameGraphView(QWidget *parent);

    /*!
      Ändert das angezeigte LiveGame auf \\pliveGame.
      */
    virtual void setLiveGame(Database::LiveGame *liveGame);

    /*!
      MUSS(!) aufgerufen werden, wenn eine neue Instanz dieses Objekts erstellt wird.
      */
    void setupView(Database::LiveGame *liveGame);

private slots:
    /*!
      Teilt Größenänderungen am View dem Koordinatensystem per CoordinateSystem::updateScales() mit, welches dann seine Skalierung anpasst, sodass alle Graphen wieder in den View passen und diesen komplett ausfüllen.
      */
    void resizeEvent(QResizeEvent *event);

    void on_coordinateSystem_dimensionsChanged(QRectF);
protected:
    Items::LiveGameCoordinateSystem* m_liveGameCoordinateSystem; //!< Das Koordinatensystem, welches alle Graphen enthält.
};

}
}


#endif // LIVEGAMEGRAPHVIEW_H
