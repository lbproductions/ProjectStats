#ifndef ENDLIVEGAMEWIDGET_H
#define ENDLIVEGAMEWIDGET_H

#include <QDialog>
#include <QPointer>

namespace Ui {
    class EndLiveGameWidget;
}

namespace Database
{
    class Place;
    class LiveGame;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

/**
* Widget, das ein LiveGame beendet. Dabei wird der Name und der Kommentar des LiveGames eingegeben.
*/
class EndLiveGameWidget : public QDialog
{
    Q_OBJECT

public:
    /**
    * Erstellt eine neue Instanz des EndLiveGameWidget für das übergebene LiveGame.
    */
    explicit EndLiveGameWidget(Database::LiveGame* livegame, QWidget *parent = 0);
    ~EndLiveGameWidget();

private slots:
    /**
    * Beendet das Spiel endgültig. Der eingebene Name und Kommentar werden für das Spiel gesetzt.
    */
    void on_pushButtonFinish_clicked();

    /**
    * Schließt das Widget ohne Änderungen am LiveGame.
    */
    void on_pushButtonCancel_clicked();

private:
    Ui::EndLiveGameWidget *ui;

    QPointer<Database::LiveGame> m_livegame;

signals:
    /**
    * Wird gesendet, wenn das Spiel endgültig beendet wird.
    */
    void liveGameClosed();
};

}
}
}

#endif // ENDLIVEGAMEWIDGET_H
