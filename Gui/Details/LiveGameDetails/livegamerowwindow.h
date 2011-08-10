#ifndef LIVEGAMEROWWINDOW_H
#define LIVEGAMEROWWINDOW_H

#include <Gui/Details/rowwindow.h>

#include "endlivegamewidget.h"
#include <Gui/Details/LiveGameDetails/livegamedetailswidget.h>
#include <Database/livegame.h>

#include <QPointer>


namespace Gui
{

namespace Details
{


//! Diese Klasse stellt eine gemeinsame Oberklasse für alle LiveGameWindows dar.
/*!
  Sie sollte eigentlich nie tatsächlich instantiiert werden, stattdessen sollte für jeden Spieltyp eine eigene Unterklasse implementiert sein.<br>
  Möchte man in die Toolbar zusätzliche Icons installieren, so muss setupToolbar neu implementiert werden und in setupToolbar die Methode der Oberklasse ausgeführt werden.
  Zudem solte man disableIcons und pauseLiveGame entsprechend anpassen, wenn dies nötig ist. Auch hier muss die Oberklassen-Methode ausgeführt werden!<br>

  */
class LiveGameRowWindow : public RowWindow
{
    Q_OBJECT
public:
    LiveGameRowWindow(Database::LiveGame* livegame, QWidget *parent = 0);
    ~LiveGameRowWindow();

protected:
    QPointer<Database::LiveGame> m_livegame;
    QPointer<LiveGameDetails::LiveGameDetailsWidget> m_liveGameDetailsWidget;

    QPointer<QToolBar> m_toolbar;

    QAction* m_actionFullScreen;
    QAction* m_actionPause;
    QAction* m_actionNewRound;
    QAction* m_actionCloseGame;
    QAction* m_actionAddDrink;
    QAction* m_actionSettings;

    /**
    * Erstellt eine neue Toolbar mit den zugehörigen Actions für das LiveGame.
    */
    void setupToolBar();

protected slots:

    virtual void reflectState();

    /**
    * Wird von der Action m_actionFullScreen aufgerufen. Wechelt je nach Zustand von state zwischen Fullscreen-Mode und Normal-Mode.
    */
    void setFullScreen(bool state);

    /**
    * Wird von der Action m_actionPause aufgerufen. Wechselt je nach Zustand von state zwischen Pausieren und Fortsetzen des LiveGames.
    */
    void pauseLiveGame(bool pause);

    /**
    * Wird von der Action m_actionCloseGame aufgerufen. Öffnet das EndLiveGameWidget und verknüpft dessen Signal liveGameClosed() mit dem Slot onLiveGameClosed.
    */
    void showEndGameDialog();

    /**
    * Wird von der Action m_actionNewRound aufgerufen. Wechselt je nach Zustand von state zwischen Darstellen und Löschen des NewDokoRoundWidgets.
    */
    virtual void showNewRoundDialog();

    void showAddDrinkDialog();
};
}}

#endif // LIVEGAMEROWWINDOW_H
