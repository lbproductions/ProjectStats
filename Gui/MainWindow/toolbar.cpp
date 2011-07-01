#include "toolbar.h"

#include "mainwindow.h"
#include "actionsmanager.h"

#include <QMenu>
#include <QContextMenuEvent>

using namespace Gui::MainWindow;

ToolBar::ToolBar(MainWindow *parent) :
    QToolBar(parent),
    m_actions(parent->actionsManager())
{
    setWindowTitle(parent->windowTitle());
    setIconSize(QSize(50,44));
    setMovable(false);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenu(QPoint)));

    addAction(m_actions->actionGameWizard);
    addAction(m_actions->actionNewPlayer);
    addAction(m_actions->actionNewPlace);
    addAction(m_actions->actionNewDrink);
}

void ToolBar::contextMenu(QPoint /*point*/)
{
    // http://bugreports.qt.nokia.com/browse/QTBUG-11271
    // http://bugreports.qt.nokia.com/browse/QTBUG-14433
    // Geht nicht mit unifiedtoolbar on mac.
}
