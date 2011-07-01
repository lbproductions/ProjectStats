#include "sidebarstatusbar.h"

#include "sidebar.h"
#include "sidebarstatusbardragbutton.h"

#include <handler.h>
#include <Gui/MainWindow/mainwindow.h>
#include <Gui/MainWindow/actionsmanager.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QMenu>

using namespace Gui::MainWindow;

SidebarStatusBar::SidebarStatusBar(MainWindow *mainWindow, Sidebar *parent) :
    QFrame(parent),
    m_mainWindow(mainWindow)
{
    this->setStyleSheet("Gui--MainWindow--SidebarStatusBar {"
			"margin: 0px;"
			"padding: 0px;"
		    "background-image: url(:/graphics/styles/mac/statusbar/background); "
		    "background-repeat: repeat-x;"
		    "background-position: top left;"
		    "background-origin: margin;"
		  "}");
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(12);
    setFixedHeight(23);

    QPushButton *toolButtonOptions = new QPushButton();
    toolButtonOptions->setFixedSize(28,23);
    toolButtonOptions->setText("");
    QMenu *optionsMenu = createOptionsMenu();
    toolButtonOptions->setMenu(optionsMenu);
    toolButtonOptions->setStyleSheet("QPushButton {"
			    "background-image: url(:/graphics/styles/mac/sidebar/optionsbutton);"
			    "border: none;"
			  "}"
			 "QPushButton:pressed {"
			     "background-image: url(:/graphics/styles/mac/sidebar/optionsbutton_pressed);"
			     "border: none;"
			   "}"
			     "QPushButton::menu-indicator {"
				  "image: url(notexistent.jpg);"
			      "}");

    layout->addWidget(toolButtonOptions);

    layout->addStretch(1);

    m_dragButton = new SidebarStatusBarDragButton(this);
    layout->addWidget(m_dragButton);

    setLayout(layout);
}

QMenu *SidebarStatusBar::createOptionsMenu()
{
    QMenu *optionsMenu = new QMenu();

    QMenu *newMenu = new QMenu("New");
    newMenu->addAction(m_mainWindow->actionsManager()->actionNewPlayersFolder);
    newMenu->addAction(m_mainWindow->actionsManager()->actionNewGamesFolder);
    newMenu->addAction(m_mainWindow->actionsManager()->actionNewPlacesFolder);
    newMenu->addAction(m_mainWindow->actionsManager()->actionNewDrinksFolder);
    newMenu->addAction(m_mainWindow->actionsManager()->actionNewLeague);

    optionsMenu->addMenu(newMenu);

    return optionsMenu;
}
