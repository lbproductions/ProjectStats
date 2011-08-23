#ifndef SIDEBARSTATUSBARDRAGBUTTON_H
#define SIDEBARSTATUSBARDRAGBUTTON_H

#include <QPushButton>

namespace Gui
{

namespace MainWindow
{

class SidebarStatusBar;

class SidebarStatusBarDragButton : public QPushButton
{
    Q_OBJECT
public:
    SidebarStatusBarDragButton(SidebarStatusBar* parent);

signals:
    void dragged(int px);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    int m_horizontalPosition;

};

}
}

#endif // SIDEBARSTATUSBARDRAGBUTTON_H
