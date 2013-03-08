#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

class QStackedWidget;
class QVBoxLayout;

namespace Database
{
    class Categorie;
    class ChildCategorie;
}

//! In diesem namespace sollten sich alle GUI Elemente befinden.
/*!
  */
namespace Gui
{

namespace Misc
{
    class Splitter;
}

//! Fasst alle Komponenten des MainWindow in einem namespace zusammen.
/*!
  */
namespace MainWindow
{

namespace Views
{
    class View;
}

class Sidebar;
class MenuBar;
class ActionsManager;
class ToolBar;
class Statusbar;

//! Das Hauptfenster der Applikation.
/*!
  Zu jedem Hauptfenster ist immer genau eine Datenbank geöffnet und es kann nur ein Hauptfenster zur gleichen Zeit offen sein.<br>
  Das MainWindow erstellt und verwaltet alle seine enthaltenen Komponenten und sorgt für die Kommunikation zwischen diesen.<br>
  <br>
  Aufbau:
  \verbatim
  +----ToolBar---+
  |Si|           |
  |de|   View    |
  |Ba|           |
  |r |           |
  +--+-----------+
  \endverbatim
  Wird in der Sidebar eine neue Kategorie angewählt, wird das neue Model der ItemsList mitgeteilt.<br>
  Interaktionen mit der Liste führen zu Anzeigen im DetailsWidget oder neu geöffneten Fenstern
  */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /*!
      Erstellt ein neues MainWindow. Dabei werden alle Komponenten initialisiert und gespeicherte Einstellungen geladen.
      */
    MainWindow(QWidget *parent = 0);

    /*!
      Speichert die Fenstergröße und Splitter-Einstellungen.
      */
    ~MainWindow();

    /*!
      \return Die Actions-Klasse für dieses MainWindow.
      */
    ActionsManager *actionsManager() const;

    /*!
      Fragt den Benutzer, ob er die Datenbank wirklich schließen will. Dabei hat er die Möglichkeit diesen Dialog in Zukunft nicht mehr anzuzeigen.
      */
    void closeEvent(QCloseEvent *event);

    Statusbar * statusBar() const;

    Sidebar* sidebar() const;

private slots:
    /*!
      Dieser Slot wird aufgerufen, wenn in der Sidebar eine neue Categorie angewählt wurde.<br>
      Dann wird das Model der ItemsList auf das der neuen Kategorie gesetzt.
      */
    void on_sidebar_categorieChanged(Database::ChildCategorie*);

private:
    QPointer<ToolBar> m_toolbar; //!< Die Toolbar am oberen Rand des Fensters.
    QPointer<Sidebar> m_sidebar; //!< Die Sidebar am linken Rand des Fensters.
    QPointer<Misc::Splitter> m_verticalSplitter; //!< Enthält links die Sidebar und rechts die ItemsList und DetailsWidget (beide in m_horizontalSplitter).
    QPointer<MenuBar> m_menubar; //!< Verwaltet die Menubar Elemente
    QPointer<ActionsManager> m_actionsManager; //!< Verwaltet alle möglichen Gui-Aktionen.
    QPointer<QStackedWidget> m_stackedWidget;
    QPointer<QVBoxLayout> m_vBoxLayout;
    QPointer<Statusbar> m_statusbar;

    /*!
      Initialisiert alle Komponenten und setzt sie korrekt zusammen.
      */
    void setupMainspace();

    /*!
      Liest nach dem Erstellen des Fensters alle möglichen Einstellungen, wie Größe und Splitter-Positionen aus.
      */
    void restoreSettings();

    /*!
      Speichert beim Beenden des Fensters alle möglichen Einstellungen, wie Größe und Splitter-Positionen.
      */
    void saveSettings();
};

}

}

#endif // MAINWINDOW_H
