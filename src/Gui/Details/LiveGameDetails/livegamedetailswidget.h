#ifndef LIVEGAMEDETAILSWIDGET_H
#define LIVEGAMEDETAILSWIDGET_H

#include <Gui/Details/detailswidget.h>

class QTableWidget;

namespace Database
{
    class LiveGame;
}

namespace Gui
{

namespace Graphs
{
    class LiveGameGraphView;
}

namespace Details
{

class LiveGameRowWindow;

namespace LiveGameDetails
{

class LiveGameInfoGroupBox;
class LiveGameRoundTable;

//! Diese Klasse stellt eine gemeinsame Oberklasse für alle LiveGameWidgets dar.
/*!
    Sie sollte eigentlich nie tatsächlich instantiiert werden, stattdessen sollte für jeden Spieltyp eine eigene Unterklasse implementiert sein.<br>
    Bei der Implementierung einer neuen Unterklasse muss im Konstruktor setupWidget() und initializeItems() ausgeführt werden. Verwendet man eigene Widgets,
    so müssen entsprechend setupWidget(), initializeItems(), fillWidget() und resizeEvent() angepasst werden. Dabei ist es wichtig, dass jeweils die Oberklassen-Methoden
    von der jeweiligen Methode bei der Reimplementierung aufgerufen werden.<br>
    Wichtig ist außerdem, dass showRoundWidget() mit einem für das Game entsprechendem NewRoundWidget implementiert wird.
*/
class LiveGameDetailsWidget : public DetailsWidget
{
    Q_OBJECT

public:
    LiveGameDetailsWidget(Database::LiveGame* livegame, QWidget *parent = 0);

    /**
     * Virtuelle Methode, die die zugehörigen Widgets anpasst und zu Layouts hinzufügt. Muss bei Reimplementierung aufgerufen werden.
     */
    virtual void setupWidget();

    /**
     * Initialisiert die einzelnen Items für dieses Widget. Bei Reimplementierung muss diese Methode aufgerufen werden als letzter Aufruf dieser!
     */
    virtual void initializeItems();

protected slots:
    void on_currentRoundChanged();

    void resizeEvent(QResizeEvent* /*event*/);

    void fillWidget();

protected:
    friend class ::Gui::Details::LiveGameRowWindow;

    QPointer<Database::LiveGame> m_livegame;

    QPointer<LiveGameDetails::LiveGameInfoGroupBox> m_infoBox;

    QPointer<LiveGameDetails::LiveGameRoundTable> m_roundTable;

    QTableWidget* m_playerTotalPointsTable;

    QPointer<Gui::Graphs::LiveGameGraphView> m_graph;


    void updateSizes();
};

}
}
}

#endif // LIVEGAMEDETAILSWIDGET_H
