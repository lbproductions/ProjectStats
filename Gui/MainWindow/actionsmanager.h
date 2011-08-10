#ifndef ACTIONSMANAGER_H
#define ACTIONSMANAGER_H

#include <QObject>
#include <QPointer>
#include <QKeySequence>

class QAction;

namespace Gui
{

namespace MainWindow
{

class MainWindow;

//! Verwaltet QActions, die in unserer Gui eingesetzt werden.
/*!
  Jede Action, die wir verwenden sollte hier mit Hilfe der Funktion constructAction() erstellt werden und dann mit einem eigenen Slot verknüpft werden.<br>
  Diese Actions werden dann vom MainWindow, beziehungsweise ihren Komponenten verwendet.<br>
  <br>
  Dieses Schema sollten wir eventuell auch für andere Fenster übernehmen, das ist aber wohl nicht zwingend nötig.
  */
class ActionsManager : public QObject
{
    Q_OBJECT
public:
    /*!
      Erstellt eine Action-Verwaltungsklasse für das MainWindow \\pparent.
      */
    explicit ActionsManager(MainWindow *parent = 0);

    /*!
      Diese Action öffnet einen GameWizard mit MainWindow als parent.
      \see Slot: openGameWizard()
      */
    QAction* actionGameWizard;

    /*!
      Diese Action erstellt einen neuen Spieler und öffnet das zugehörige PlayerWidget, um ihn zu editieren.
      \see Slot: openNewPlayer()
      */
    QAction* actionNewPlayer;

    /*!
      Diese Action öffnet ein NewPlaceWidget mit MainWindow als parent.
      \see Slot: openNewPlace()
      */
    QAction* actionNewPlace;

    /*!
      Diese Action öffnet ein NewDrinkWidget mit MainWindow als parent.
      \see Slot: openNewDrink()
      */
    QAction* actionNewDrink;

    /*!
      Diese Action schließt das aktuelle MainWindow, fragt den User nach einer Datenbankdatei und öffnet dafür ein neues MainWindow.
      \see switchDatabase()
      */
    QAction* actionSwitchDatabase;

    QAction *actionCheckForUpdates;

    QAction *actionNewPlayersFolder;
    QAction *actionNewGamesFolder;
    QAction *actionNewPlacesFolder;
    QAction *actionNewDrinksFolder;
    QAction *actionNewLeague;

    QAction * actionUndo;
    QAction * actionRedo;
    QAction * actionCut;
    QAction * actionCopy;
    QAction * actionPaste;

    QAction * actionShowDatabase;

public slots:
    /*!
      Wird von der Action actionGameWizard() aufgerufen.
      */
    void openGameWizard();

    /*!
      Wird von der Action actionNewPlayer() aufgerufen.
      */
    void openNewPlayer();

    /*!
      Wird von der Action actionNewPlace() aufgerufen.
      */
    void openNewPlace();

    /*!
      Wird von der Action actionNewDrink() aufgerufen.
      */
    void openNewDrink();

    /*!
      Wird von der Action actionSwitchDatabase() aufgerufen.
      */
    void switchDatabase();

    void checkForUpdates();

    void newPlayersFolder();
    void newGamesFolder();
    void newPlacesFolder();
    void newDrinksFolder();
    void newLeagueFolder();

    void showDatabase();

private:
    /*!
      Erstellt eine neue QAction mit Namen \p name, dem Icon \p iconPath und der optionalen Tastenkombination \p shortcut.
      */
    QAction *constructAction(const QString& name, const QString& iconPath, const QKeySequence &shortcut = QKeySequence());

    void createActions();

    QPointer<MainWindow> m_mainWindow; //!< Das MainWindow mit dem die Actions arbeiten.

};

}

}

#endif // ACTIONSMANAGER_H
