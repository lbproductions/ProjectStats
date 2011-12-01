#include "mainwindow.h"


#include <Misc/messagesystem.h>
#include "actionsmanager.h"
#include "menubar.h"
#include "toolbar.h"
#include "statusbar.h"
#include "Sidebar/sidebar.h"
#include "Sidebar/sidebartreeview.h"

#include <Misc/handler.h>
#include <LBDatabase/LBDatabase.h>
#include <Gui/MainWindow/Views/view.h>
#include <Database/Categories/childcategorie.h>
#include <Gui/Misc/splitter.h>
#include <Gui/Misc/macwindowcontroller.h>

#include <QScrollArea>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QScrollBar>
#include <QCheckBox>
#include <QStackedWidget>
#include <QVBoxLayout>

using namespace Gui::MainWindow;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    m_actionsManager(new ActionsManager(this))
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("ProjectStats");

    setupMainspace();

    this->setUnifiedTitleAndToolBarOnMac(true);
    m_toolbar = new ToolBar(this);
    addToolBar(m_toolbar);

    m_menubar = new MenuBar(this);
    this->setMenuBar(m_menubar);

    restoreSettings();

#ifdef Q_WS_MAC
    setUpFullScreenButton(this);
#endif
}

MainWindow::~MainWindow()
{
    saveSettings();

    if(m_menubar)
    {
        m_menubar->deleteLater();
    }
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("MainWindow/geometry", saveGeometry());
    settings.setValue("MainWindow/windowState", saveState());
    settings.setValue("MainWindow/verticalSplitter/geometry", m_verticalSplitter->saveGeometry());
    settings.setValue("MainWindow/verticalSplitter/windowState", m_verticalSplitter->saveState());
}

void MainWindow::restoreSettings()
{
    QSettings settings;
    restoreState(settings.value("MainWindow/windowState").toByteArray());
    restoreGeometry(settings.value("MainWindow/geometry").toByteArray());
    m_verticalSplitter->restoreState(settings.value("MainWindow/verticalSplitter/windowState").toByteArray());
    m_verticalSplitter->restoreGeometry(settings.value("MainWindow/verticalSplitter/geometry").toByteArray());
#ifdef Q_WS_MAC
    //workaround for http://bugreports.qt.nokia.com/browse/QTBUG-10500
    // Unified toolbar covers parts of the central widget
    resize(width(), height()-1);
    resize(width(), height()+1);
#endif
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    if(settings.value("MainWindow/confirmClose",true).toBool())
    {
	QMessageBox msg(this);
	msg.setText(tr("Do you really want to close the database?"));
	msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msg.setDefaultButton(QMessageBox::Yes);
	msg.setIcon(QMessageBox::Question);

	QCheckBox dontPrompt(tr("Do not ask again"), &msg);
	dontPrompt.blockSignals(true);

	msg.addButton(&dontPrompt, QMessageBox::ActionRole);

	int ret = msg.exec();
	if(ret == QMessageBox::No)
	{
	    event->ignore();
	}
	else
	{
	    event->accept();
	    if(dontPrompt.checkState() == Qt::Checked )
	    {
		settings.setValue("MainWindow/confirmClose",false);
	    }
	}
    }
    else
    {
	event->accept();
    }
 }

void MainWindow::setupMainspace()
{
    m_verticalSplitter = new Misc::Splitter(Qt::Horizontal);

    m_sidebar = new Sidebar(this);
    connect(m_sidebar->treeView(),SIGNAL(categorieChanged(Database::ChildCategorie*)),
	    this,SLOT(on_sidebar_categorieChanged(Database::ChildCategorie*)));
    connect(m_sidebar,SIGNAL(dragged(int)),m_verticalSplitter,SLOT(myMoveSplitter(int)));
    m_verticalSplitter->addWidget(m_sidebar);

    setCentralWidget(m_verticalSplitter);

    QWidget *viewArea = new QWidget(m_verticalSplitter);
    m_vBoxLayout = new QVBoxLayout(viewArea);
    viewArea->setContentsMargins(0,0,0,0);
    m_vBoxLayout->setSpacing(0);
    m_vBoxLayout->setContentsMargins(0,0,0,0);
    m_verticalSplitter->addWidget(viewArea);

    m_stackedWidget = new QStackedWidget(viewArea);
    m_vBoxLayout->addWidget(m_stackedWidget);

    m_statusbar = new Statusbar(this);
    m_vBoxLayout->addWidget(m_statusbar);

    m_verticalSplitter->setStretchFactor(0, 0);
    m_verticalSplitter->setStretchFactor(1, 1);

    on_sidebar_categorieChanged(m_sidebar->treeView()->selectedCategorie());
}

Statusbar *MainWindow::statusBar() const
{
    return m_statusbar;
}

void MainWindow::on_sidebar_categorieChanged(Database::ChildCategorie* c)
{
    if(c == 0 || c->view() == 0)
    {
        return;
    }

    Views::View *view = c->view();
    m_stackedWidget->addWidget(view);
    m_stackedWidget->setCurrentWidget(view);
    view->updateStatusbar();
    if(view->windowTitle().isEmpty())
    {
        setWindowTitle("ProjectStats");
    }
    else
    {
        setWindowTitle(QString::fromUtf8("ProjectStats \u2013 ")+view->windowTitle());
    }
    setWindowIcon(view->windowIcon());
}

ActionsManager *MainWindow::actionsManager() const
{
    return m_actionsManager;
}
