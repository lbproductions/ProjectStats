#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>

namespace Gui
{

namespace Graphs
{

//! Bildet die Oberklasse für alle Graphenanzeigen.
/*!
  Bis jetzt macht diese Klasse eigentlich nicht, außer eine leere QGraphicsScene zu initialisieren und ein paar Einstellungen in ihr vorzunehmen (wie z.B. Anti-Aliasing).
  */
class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    /*!
      Erstellt ein GraphView.
      */

    explicit GraphView(QWidget *parent = 0);

public slots:
    void setFullscreen();

    void setNormalMode();
};

}

}

#endif // GRAPHVIEW_H
