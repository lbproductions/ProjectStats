#include "sidebarstatusbardragbutton.h"

#include "sidebarstatusbar.h"

#include <QMouseEvent>

using namespace Gui::MainWindow;

SidebarStatusBarDragButton::SidebarStatusBarDragButton(SidebarStatusBar *parent) :
    QPushButton(parent),
    m_horizontalPosition(0)
{
    setFixedSize(17,23);
    setText("");
    setStyleSheet("QPushButton {"
			    "background-image: url(:/graphics/styles/mac/sidebar/drag);"
			    "border: none;"
			  "}");
    setCursor(QCursor(Qt::SplitHCursor));
}

void SidebarStatusBarDragButton::mousePressEvent(QMouseEvent *e)
{
    m_horizontalPosition = e->pos().x();
}

void SidebarStatusBarDragButton::mouseMoveEvent(QMouseEvent *e)
{
    if(m_horizontalPosition == 0)
    {
	m_horizontalPosition = e->pos().x();
	return;
    }
    int offset = e->pos().x() - m_horizontalPosition;
    emit dragged(offset);
}
