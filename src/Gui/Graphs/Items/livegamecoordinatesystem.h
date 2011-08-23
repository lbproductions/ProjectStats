#ifndef LIVEGAMECOORDINATESYSTEM_H
#define LIVEGAMECOORDINATESYSTEM_H

#include "coordinatesystem.h"

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
//! Stellt Graphen für Punkte eines LiveGames dar.
/*!
  Fügt für jeden Spieler aus dem LiveGame einen LiveGamePlayerPointsGraph hinzu.<br>
  Außerdem werden eine Nulllinie, Linien in 10 Punkte Schritten und senkrechte Linien, wenn jeder Spieler einmal gegeben hat angezeigt.
  */
class LiveGameCoordinateSystem : public CoordinateSystem
{
    Q_OBJECT
public:
    /*!
      Erstellt ein Koordinatensystem und Graphen, die die Punktzahl aller Spieler anzeigen.
      */
    LiveGameCoordinateSystem(Database::LiveGame *liveGame);

    /*!
      MUSS(!) aufgerufen werden, wenn eine neues Instanz dieses Objekts erstellt wird.
      */
    void setupSystem();

    /*!
      Zeichnet die Nulllinie, Linien in 10 Punkte Schritten und senkrechte Linien, wenn jeder Spieler einmal gegeben hat angezeigt.
      */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    /*!
      Erstellt die Graphen für alle Spieler.
      */
    virtual void addGraphsForPlayers();

    Database::LiveGame* m_liveGame; //!< Das Spiel, welches das Koordinatensystem widerspiegelt.
};

}
}
}

#endif // LIVEGAMECOORDINATESYSTEM_H
