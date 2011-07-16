#ifndef DOKOLIVEGAMEROWWINDOW_H
#define DOKOLIVEGAMEROWWINDOW_H

#include <Gui/Details/LiveGameDetails/livegamerowwindow.h>

#include <QPointer>

namespace Database
{
    class DokoLiveGame;
}

namespace Gui
{

namespace Details
{

class DokoLiveGameDetailsWidget;

/**
* Ist das MainWindow des LiveGames. Ist für die Toolbar und die damit zusammenhängenden Actions zuständig. Enthält das LiveGameStatsWidget.
*/
class DokoLiveGameRowWindow : public LiveGameRowWindow
{
    Q_OBJECT
public:
    /**
    * Erstellt eine neue Instanz LiveGameWidget für das übergebene dokogame. Dabei wird ein neues LiveGameStatsWidget erstellt und mit dessen Signals verknüpft. Zudem wird setupToolBar ausgeführt.
    */
    explicit DokoLiveGameRowWindow(Database::DokoLiveGame* dokogame, QWidget *parent = 0);

    /**
    * Erstellt eine neue Toolbar mit den zugehörigen Actions für das LiveGame.
    */
    void setupToolBar();

private:
    QPointer<Database::DokoLiveGame> m_dokolivegame;

    QAction* m_actionSchmeisserei;

private slots:

    /**
    * Wird von der Action m_actionSchmeisserei aufgerufen. Zeigt das SchmeissereiWidget an
    */
    void showNewSchmeissereiDialog();

    /**
    * Wird von der Action m_actionPause aufgerufen. Wechselt je nach Zustand von state zwischen Pausieren und Fortsetzen des LiveGames.
    */
    void reflectState();
};

}
}
#endif // DOKOLIVEGAMEROWWINDOW_H
