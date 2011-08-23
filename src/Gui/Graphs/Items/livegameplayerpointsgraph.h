#ifndef LIVEGAMEPLAYERPOINTSGRAPH_H
#define LIVEGAMEPLAYERPOINTSGRAPH_H

#include "graph.h"

namespace Database
{
class LiveGame;
class Player;
class Round;
}

namespace Gui
{

namespace Graphs
{

namespace Items
{

class LiveGameCoordinateSystem;

//! Stellt einen Graphen für die Punktzahl eines Spieler beim LiveGame dar.
/*!
  Dafür werden zunächst Punkt für jede bestehende Runde hinzugefügt.<br>
  Anschließend wird das Spiel beobachtet und beim Beenden einer Runde ein neuer Punkt erstellt.
  */
class LiveGamePlayerPointsGraph : public Graph
{
    Q_OBJECT
public:
    /*!
      Erstellt einen Graphen, der die Punkte des Spielers \p player im Spiel \p liveGame im Koordinaten \p coordinateSystem darstellt.
      */
    LiveGamePlayerPointsGraph(Database::Player *player, Database::LiveGame *liveGame, LiveGameCoordinateSystem *coordinateSystem);

    /*!
      MUSS(!) aufgerufen werden, wenn eine neues Instanz dieses Objekts erstellt wird.
      */
    void setupGraph();

    Database::Player* player();

public slots:
    /*!
      Dieser Slot wird aufgerufen, wenn im Spiel eine Runde beendet wird. Dann wird die Punktzahl des Spielers berechnet und als Punkt hinzugefügt.
      */
    virtual void addRound(::Database::Round*);

protected:
    /*!
      Liest die bestehenden Runden ein und fügt die Punkte daraus hinzu.
      */
    void readPlayerPoints();

    QPointer<Database::Player> m_player; //!< Der Spieler, den dieser Graph anzeigt.
    QPointer<Database::LiveGame> m_liveGame; //!< Das LiveGame dessen Punkte angezeigt werden.
    int m_totalPoints; //!< Wird gebraucht, um die Gesamtpunktzahl des Spielers zu speichern.
};

}
}
}

#endif // LIVEGAMEPLAYERPOINTSGRAPH_H
