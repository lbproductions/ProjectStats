#ifndef LIVEGAMEDETAILSWIDGET_H
#define LIVEGAMEDETAILSWIDGET_H

#include <Gui/Details/detailswidget.h>

#include <Gui/Details/LiveGameDetails/beerwidget.h>
#include <Gui/Details/LiveGameDetails/adddrinkwidget.h>
#include <Gui/Details/LiveGameDetails/livegameroundtable.h>
#include <Gui/Details/LiveGameDetails/livegameinfogroupbox.h>
#include <Gui/Graphs/livegamegraphview.h>
#include <Gui/Details/LiveGameDetails/livegamesettingswidget.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QTime>
#include <QTimer>
#include <QTextEdit>

namespace Database{
    class LiveGame;
}

namespace Gui{

    namespace Details{

        namespace LiveGameDetails{


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

    /**
     * Gibt den Status, ob das LiveGameWindow im Fullscreen oder nicht befindet, zurück.
     */
    bool isFullscreen();

    /**
     * Überprüft ob das laufende Spiel sein Ende gefunden hat, wenn dies festgelegt wurde
     */
    virtual void checkForEndOfGame();

public slots:

    /**
     * Das LiveGame wird angehalten. Dabei wird der Timer gestoppt und die QTime für die Pause gestartet.
     */
    virtual void pauseGame();

    /**
     * Das LiveGame wird fortgesetzt. Dabei wird die Länge der Pause zur schon bestehenden Länge hinzuaddiert. Der Timer wird gestartet und dessen Signal mit updateWidget verknüpft.
     */
    virtual void resumeGame();

    /**
     * Löscht die currentRound.
     */
    virtual void closeGame();

    /**
     * Aktualisiert das Widget
     */
    virtual void updateWidget();

    /**
     * Aktualisiert die Stats etc nach dem hinzufügen einer neuen Runde
     */
    virtual void onRoundCreated();

    /**
     * Wird ausgeführt um ein Spiel nachträglich anzuschauen oder weiterzuführen. Alle bestehenden Runden und Drinks des Spiels werden hinzugefügt. Auch die Zeit wird auf den richtigen Zeitpunkt gesetzt.
     */
    virtual void fillWidget();

    /**
     * Löscht das aktuell angezeigte obere Element wie RoundWidget, DrinkWidget oder SchmeissereiWidget aus dem Layout.
     */
    void hideHeadHorizontalWidget();

    /**
     * Zeigt das AddDrinkWidget an.
     */
    void showAddDrinkWidget();

    /**
     * Gibt das BeerWidget zurück.
     */
    QPointer<BeerWidget> beerwidget();

    /**
     * Wird nach dem Hinzufügen von Drinks ausgeführt.
     */
    void onDrinkDealed();

    /**
    * Setzt die Einstellungen und das Design für den Fullscreen
    */
    void setFullscreenMode();


    /**
    * Setzt die Einstellungen und das Design für den Normalmode
    */
    void setNormalMode();

    /**
    * Wird bei einer Änderung im LiveGameSettingsWidget aufgerufen. Ist dafür verantwortlich die dort ausgewählten Widgets anzuzeigen.
    */
    virtual void onSettingsChanged();

    /**
     * Zeigt das entsprechende NewRoundWidget an.
     */
    virtual void showRoundWidget();

    /**
     * Zeigt das LiveGameSettingsWidget an.
     */
    virtual void showLiveGameSettingsWidget();


protected slots:

    /*!
      Aktualisiert die Schriftgrößen im widget.
      */
    void resizeEvent(QResizeEvent *);

protected:

    QVBoxLayout* m_layout;
    QVBoxLayout* m_newItemLayout;
    QHBoxLayout* m_centerLayout;

    QSplitter* m_splitter;
    QTimer* timer;
    QTime timePause;
    QTime timeGame;
    QTime gameLength;
    QList< Database::Player* > m_playerlist;

    int lengthPause;
    bool m_fullscreen;

    QPointer<Database::LiveGame> m_livegame;

    QPointer<LiveGameDetails::LiveGameInfoGroupBox> m_infoBox;

    QPointer<LiveGameDetails::BeerWidget> m_beerwidget;

    QPointer<LiveGameDetails::AddDrinkWidget> m_addDrinkWidget;

    QPointer<LiveGameDetails::LiveGameRoundTable> m_roundTable;

    QPointer<LiveGameDetails::LiveGameSettingsWidget> m_settingsWidget;

    QTableWidget* m_playerTotalPointsTable;

    QPointer<Gui::Graphs::LiveGameGraphView> m_graph;

    QTextEdit* m_gamecomment;

signals:

    /**
     * Wird nach dem Erstellen einer Runde im NewDokoRoundWidget gesendet.
     */
    void roundCreated();

    /**
     * Wird nach dem Hinzufügen einer Schmeisserei im SchmeissereiWidget gesendet.
     */
    void schmeissereiAdded();

    /**
     * Wird nach dem Hinzufügen von Drinks gesendet.
     */
    void drinkDealed();

    /**
     * Wird gesendet, wenn das Widget nachträglich über fillWidget geöffnet wird und das Spiel schon beendet ist.
     */
    void finishedGameShown();

    /**
     * Wird gesendet, wenn das laufende Spiel durch irgendwelche Konditionen beendet wurde.
     */
    void gameEnded();

};

}}}

#endif // LIVEGAMEDETAILSWIDGET_H
