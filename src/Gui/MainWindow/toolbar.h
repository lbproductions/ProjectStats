#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QPointer>

namespace Gui
{

namespace MainWindow
{

class MainWindow;
class ActionsManager;

//! Die Toolbar des MainWindow.
/*!
  Diese enthält Buttons für die wichtigsten Aktionen der GUI.<br>
  Später könnte ein Kontextmenü zur Anpassung der Buttons gereitgestellt werden.
  */
class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    /*!
      Erstellt die Toolbar für das MainWindow \\pparent.
      */
    explicit ToolBar(MainWindow *parent = 0);

protected slots:
    void contextMenu(QPoint);

private:
    QPointer<ActionsManager> m_actions; //!< Das Actions-Objekt des MainWindow.
};

}

}

#endif // TOOLBAR_H
