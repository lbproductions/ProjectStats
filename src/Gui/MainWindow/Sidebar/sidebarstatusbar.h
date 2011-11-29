#ifndef SIDEBAROPTIONS_H
#define SIDEBAROPTIONS_H

#include <QFrame>
#include <QPointer>

class QMenu;

namespace Gui
{

namespace MainWindow
{

class Sidebar;
class SidebarStatusBarDragButton;
class MainWindow;

class SidebarStatusBar : public QFrame
{
    Q_OBJECT
public:
    explicit SidebarStatusBar(MainWindow *mainWindow, Sidebar *parent = 0);

friend class Sidebar;
private:
    SidebarStatusBarDragButton* m_dragButton;
    MainWindow* m_mainWindow;

    QMenu *createOptionsMenu();
};
}
}

#endif // SIDEBAROPTIONS_H
