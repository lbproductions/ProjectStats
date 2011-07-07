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

    /**
    * Erstellt eine neue Toolbar mit den zugehörigen Actions für das LiveGame.
    */
    virtual void setupToolBar();

protected:

    QPointer<Database::LiveGame> m_livegame;
    QPointer<Gui::Details::LiveGameDetails::EndLiveGameWidget> m_endLiveGameWidget;
    QPointer<LiveGameDetails::LiveGameDetailsWidget> m_liveGameDetailsWidget;

    QPointer<QToolBar> m_toolbar;

    QAction* m_actionFullScreen;
    QAction* m_actionPause;
    QAction* m_actionNewRound;
    QAction* m_actionCloseGame;
    QAction* m_actionAddDrink;
    QAction* m_actionSettings;

protected slots:

    /**
    * Wird von der Action m_actionFullScreen aufgerufen. Wechelt je nach Zustand von state zwischen Fullscreen-Mode und Normal-Mode.
    */
    void setFullScreen(bool state);

    /**
    * Wird von der Action m_actionPause aufgerufen. Wechselt je nach Zustand von state zwischen Pausieren und Fortsetzen des LiveGames.
    */
    virtual void pauseLiveGame(bool state);

    /**
    * Wird von der Action m_actionCloseGame aufgerufen. Öffnet das EndLiveGameWidget und verknüpft dessen Signal liveGameClosed() mit dem Slot onLiveGameClosed.
    */
    void finishLiveGame();

    /**
    * Wird vom EndLiveGameWidget nach dessen Bestätigung aufgerufen. Ruft closeGame() vom LiveGameStatsWidget und close() von sich selbst auf.
    */
    void onLiveGameClosed();

    /**
    * Wird von der Action m_actionAddDrink aufgerufen. Wechselt je nach Zustand von state zwischen Darstellen und Löschen des AddDrinkWidget.
    */
    void addDrink();

    /**
    * Deaktiviert alle Actions außer der des FullScreens. Wird benötigt um bereits abgeschlossene Spiele kenntlich zu machen.
    */
    virtual void disableIcons();


    /**
    * Deaktiviert entsprechende Icons, die nicht mehr aktiviert werden dürfen, nachdem das Game beendet wurde.
    */
    virtual void onGameEnded();

    /**
    * Zeigt/Löscht das SettingsWidget für das LiveGame
    */
    void showSettings();

    /**
    * Wird von der Action m_actionNewRound aufgerufen. Wechselt je nach Zustand von state zwischen Darstellen und Löschen des NewDokoRoundWidgets.
    */
    void newRound();

    /**
    * Führt fillWidget des LiveGameStatsWidget aus.
    */
    void fillWidget();
};
}}

#endif // LIVEGAMEROWWINDOW_H
