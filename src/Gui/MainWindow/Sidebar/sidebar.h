#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QPointer>

namespace Gui
{

namespace MainWindow
{

class MainWindow;

class SidebarTreeView;
class SidebarStatusBar;


class Sidebar : public QWidget
{
    Q_OBJECT
public:
    explicit Sidebar(MainWindow *parent);

    SidebarTreeView *treeView() const;

signals:
    void dragged(int px);

private:
    SidebarTreeView* m_treeView;
#ifdef Q_WS_MAC
    SidebarStatusBar* m_options;
#endif

};
}
}

#endif // SIDEBAR_H
