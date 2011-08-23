#include "sidebar.h"

#include "sidebartreeview.h"
#include "sidebarstatusbar.h"
#include "sidebarstatusbardragbutton.h"
#include "../mainwindow.h"

#include <QVBoxLayout>
#include <QResizeEvent>
#include <QSize>

using namespace Gui::MainWindow;

Sidebar::Sidebar(MainWindow *parent) :
    QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    m_treeView = new SidebarTreeView(this);
    layout->addWidget(m_treeView);

#ifdef Q_WS_MAC
    m_options = new SidebarStatusBar(parent, this);
    connect(m_options->m_dragButton,SIGNAL(dragged(int)),this,SIGNAL(dragged(int)));
    layout->addWidget(m_options);
#endif
    setLayout(layout);
}

SidebarTreeView *Sidebar::treeView() const
{
    return m_treeView;
}
