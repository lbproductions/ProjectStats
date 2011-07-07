#ifndef DOKOLIVEGAMEDETAILSWIDGET_H
#define DOKOLIVEGAMEDETAILSWIDGET_H

#include <Gui/Details/LiveGameDetails/livegamedetailswidget.h>
#include <QPointer>

namespace Database
{
    class Player;
    class DokoLiveGame;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{
    namespace DokoLiveGameDetails{
        class DokoLiveGamePlayerStatsWidget;
        class NewDokoRoundWidget;
        class DokoLiveGameSettingsWidget;
        class SchmeissereiWidget;
    }
}

/**
 * Verwaltet die Anzeige des LiveGameWidgets.
 */
class DokoLiveGameDetailsWidget : public LiveGameDetails::LiveGameDetailsWidget
{

public:
    /**
     * Erstellt das LiveGameStatsWidget. Dabei wird die UI erstellt, die QTime des Spiels gestartet und die Variablen für die Zeitmessung initialisiert.
     */
    explicit DokoLiveGameDetailsWidget(Database::DokoLiveGame *game, QWidget *parent = 0);

    ~DokoLiveGameDetailsWidget();

    /**
     * Befüllt die GroupBox mit den generellen Informationen. Die für das LiveGameStatsWidget benötigten anderen Widgets werden erstellt und zum Spliter hinzugefügt.
     * Zudem wird der Stylesheet auf normal gesetzt.
     */
    void setupWidget();

    /**
     * Wird ausgeführt um ein Spiel nachträglich anzuschauen oder weiterzuführen. Alle bestehenden Runden und Drinks des Spiels werden hinzugefügt. Auch die Zeit wird auf den richtigen Zeitpunkt gesetzt.
     */
    void fillWidget();

    void initializeItems();

private:

    QPointer<Database::DokoLiveGame> m_dokolivegame;
    QPointer<LiveGameDetails::DokoLiveGameDetails::SchmeissereiWidget> m_schmeissereiWidget;
    QPointer<LiveGameDetails::DokoLiveGameDetails::NewDokoRoundWidget> m_dokoRoundWidget;
    QPointer<LiveGameDetails::DokoLiveGameDetails::DokoLiveGamePlayerStatsWidget> m_statswidget;

public slots:

    /**
     * Zeigt das NewDokoRoundWidget an.
     */
    void showRoundWidget();

    /**
     * Wird nach dem Erstellen einer Runde ausgeführt. Dabei wird die Länge der Runde gesetzt, die erstellte Runde der RoundTable hinzugefügt,
     * die Time für die Runde zurückgesetzt, der Graph und die GroupBox der LiveGame-Informationen aktualisiert.
     */
    void onRoundCreated();

    /**
     * Zeigt das SchmeissereiWidget an.
     */
    void showSchmeissereiWidget();

    /**
     * Wird nach dem Erstellen der Schmeisserei ausgeführt. Dabei wird die Anzeige des Schmeisserei-Counts aktualisiert.
     */
    void onSchmeissereiAdded();

    /**
    * Wird bei einer Änderung im LiveGameSettingsWidget aufgerufen. Ist dafür verantwortlich die dort ausgewählten Widgets anzuzeigen.
    */
    virtual void onSettingsChanged();

signals:


protected slots:

    /*!
      Aktualisiert die Schriftgrößen im widget.
      */
    void resizeEvent(QResizeEvent *);
};
}
}

#endif // DOKOLIVEGAMEDETAILSWIDGET_H
