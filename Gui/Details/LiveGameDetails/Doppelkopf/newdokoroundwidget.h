#ifndef NEWDOKOROUNDWIDGET_H
#define NEWDOKOROUNDWIDGET_H

#include <QDialog>
#include <QPointer>

namespace Ui {
    class NewDokoRoundWidget;
}

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

/**
* Ist das Widget zum Eintragen einer neuen Runde für ein DokoLiveGame.
*/
class NewDokoRoundWidget : public QDialog
{
    Q_OBJECT

public:
    /**
    * Erstellt eine neue Instanz vom NewDokoRoundWidget für das übergebene DokoLiveGame. Setzt den StyleSheet für das Widget und führt setupWidget() aus.
    */
    explicit NewDokoRoundWidget(Database::DokoLiveGame* livegame, QWidget *parent = 0);
    ~NewDokoRoundWidget();

    /**
    * Überprüft ob die eingegebenen Daten korrekt sind. Zum Beispiel ob Re1 und Re2 gleich sind.
    */
    bool checkInputs();

private:
    Ui::NewDokoRoundWidget *ui;

    /**
    * Befüllt das Widget mit den Daten aus dem DokoLiveGame, für das das Widget erstellt wurde.
    */
    void setupWidget();

    QPointer<Database::DokoLiveGame> m_livegame;

    QList<Database::Player*> m_playerlist;

    bool m_schmeissereiState;

signals:
    /**
    * Wird gesendet, wenn eine neue Runde erstellt wurde.
    */
    void roundCreated();

private slots:
    /**
    * Wird nach einer Änderung in der ComboBox für die Trumpfabgabe aufgerufen. Verändert die Darstellung des Widgets speziell für die Trumpfabgabe.
    */
    void on_comboBoxTrumpfabgabe_currentIndexChanged(QString name);

    /**
    * Wird nach einer Änderung in der ComboBox für das Solo aufgerufen. Verändert die Darstellung des Widgets speziell für das Solo.
    */
    void on_comboBoxSolo_currentIndexChanged(QString name);

    /**
    * Wird nach einer Änderung in der ComboBox für die Hochzeit aufgerufen. Verändert die Darstellung des Widgets speziell für die Hochzeit.
    */
    void on_comboBoxHochzeit_activated(QString name);

    /**
    * Wird nach einer Änderung in der ComboBox für den zweiten Re-Mann aufgerufen. Verändert die Darstellung des Widgets speziell für den zweiten Re-Mann.
    */
    void on_comboBoxRe2_currentIndexChanged(QString name);

    /**
    * Wird nach einer Änderung in der ComboBox für den ersten Re-Mann aufgerufen. Verändert die Darstellung des Widgets speziell für den ersten Re-Mann.
    */
    void on_comboBoxRe1_currentIndexChanged(QString name);

    /**
    * Wird nach dem Klick auf den Button zum Erstellen der Runde ausgeührt. Die Daten für die Runde werden eingetragen. Im Anschluss daran wird die Runde beendet und eine neue Runde erstellt.
    */
    void on_pushButtonCreateRound_clicked();
    void on_pushButtonClose_clicked();
};

}
}
}}
#endif // NEWDOKOROUNDWIDGET_H
