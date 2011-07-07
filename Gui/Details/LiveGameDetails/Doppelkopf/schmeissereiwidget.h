#ifndef SCHMEISSEREIWIDGET_H
#define SCHMEISSEREIWIDGET_H

#include <QDialog>
#include <QPointer>

namespace Database
{
    class DokoLiveGame;
}

namespace Ui {
    class SchmeissereiWidget;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

namespace DokoLiveGameDetails{

/**
* Ist das Widget zum Hinzufügen einer Schmeisserei zu einem DokoLiveGame.
*/
class SchmeissereiWidget : public QDialog
{
    Q_OBJECT

public:
    /**
    * Erstellt eine neu Instanz des SchmeissereiWidgets für das übergebene DokoLiveGame und befüllt dabei das Widget mit Daten aus livegame.
    */
    explicit SchmeissereiWidget(Database::DokoLiveGame* livegame, QWidget *parent = 0);
    ~SchmeissereiWidget();

private slots:
    /**
    * Wird nach dem Klick auf den Button zum Hinzufügen einer Schmeisserei ausgeführt. Fügt die eingebenene Schmeisserei der aktuellen Runde des DokoLiveGames hinzu.
    */
    void on_pushButton_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::SchmeissereiWidget *ui;

    QPointer<Database::DokoLiveGame> m_livegame;

signals:
    /**
    * Wird nach dem Hinzufügen der Schmeisserei gesendet.
    */
    void schmeissereiAdded();
};

}
}
}}
#endif // SCHMEISSEREIWIDGET_H
