#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include <QPointer>

namespace Gui
{

namespace MainWindow
{

class MainWindow;
class ActionsManager;

//! Das Hauptmenü des MainWindow
/*!
  Verwaltet alle möglichten Actions in einer QMenuBar.<br>
  Dabei wird (zumindest unter OS X) darauf geachtet, dass die Icons von den Aktionen entfernt werden.
  */
class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    /*!
      Erstellt eine MenuBar für das MainWindow \\pparent.
      */
    explicit MenuBar(MainWindow *parent = 0);

private:
    /*!
      Erfragt alle File-Aktionen vom zugehörigen Actions-Objekt und fügt sie ins File-Menü ein.
      */
    void setupFileMenu();

    void setupEditMenu();

    void setupHelpMenu();

    void setupViewMenu();

    QPointer<ActionsManager> m_actionsManager; //!< Das Actions-Objekt des zugehörigen MainWindows.
    QMenu *m_fileMenu; //!< Das File-Menü.
    QMenu *m_editMenu;
    QMenu *m_helpMenu;
    QMenu *m_viewMenu;

    QMenu *m_viewGames;

};


}

}

#endif // MENUBAR_H
