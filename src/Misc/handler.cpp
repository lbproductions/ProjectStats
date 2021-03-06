#include <Misc/handler.h>

/*
#include <Database/Doppelkopf/dokolivegame.h>
*/

#include <QDebug>
#include <QPointer>
#include <QDesktopWidget>
#include <QSettings>
#include <QFileDialog>

//#include <databasewindow.h>
#include <Misc/messagesystem.h>

#ifdef Q_WS_MAC
#   include <Misc/Updater/sparkleupdater.h>
#elif defined Q_WS_WIN
#   //include <Misc/Updater/winsparkleupdater.h>
#endif

#include <Gui/MainWindow/mainwindow.h>
#include <Server/soapprojectstatsService.h>

#include <Database/database.h>
#include <Database/attribute.h>
#include <Database/player.h>
#include <Database/drink.h>
#include <Database/place.h>
#include <Database/game.h>
#include <Database/round.h>
#include <Database/livegame.h>
#include <Database/Doppelkopf/schmeisserei.h>
#include <Database/Categories/childcategorie.h>
#include <Database/Categories/parentcategorie.h>
#include <Database/livegamedrink.h>
#include <Database/taskscheduler.h>
#include <Server/server.h>

Handler::Handler(int argc, char *argv[])
    : QApplication(argc,argv),
      m_updater(0),
      m_mainThread(QThread::currentThread())
{
    setOrganizationName("LB Productions");
    setApplicationName("ProjectStats");

    setAttribute(Qt::AA_DontShowIconsInMenus,true);

    m_messagesystem = new MessageSystem();
    m_messagesystem->showWelcomeMessage();

    this->setWindowIcon(QIcon(":/icons/pslogo"));

#ifdef Q_WS_MAC
    //m_updater = new SparkleUpdater("http://dl.dropbox.com/u/140012/ProjectStats/ProjectStatsAppCast_macos.xml");
#elif defined Q_WS_WIN
    //m_updater = new WinSparkleUpdater("http://dl.dropbox.com/u/140012/ProjectStats/ProjectStatsAppCast_win.xml");
#endif

    if (m_updater) {
        m_updater->checkForUpdatesInBackground();
    }

    Database::TaskScheduler::instance()->start(QThread::HighestPriority);
}

Handler::~Handler()
{
    if(!m_database.isNull())
    {
        m_database->deleteLater();
    }
    if(!m_mainwindow.isNull())
    {
        m_mainwindow->deleteLater();
    }
    if(m_updater)
    {
        delete m_updater;
    }
    if (m_messagesystem){
        delete m_messagesystem;
    }

    Database::TaskScheduler::instance()->quit();
    //wir rufen das teil per invokeMethod auf, damit es im TaskScheduler thread startet
    QMetaObject::invokeMethod(Database::TaskScheduler::instance(),"shutdown");
}

Handler* const Handler::getInstance() {
    return qobject_cast<Handler*>(QApplication::instance());
}


void Handler::checkForUpdates()
{
    if (m_updater) {
        m_updater->checkForUpdates();
    }
}

bool Handler::showMainWindow(){


    QSettings settings;
    QFile databaseFile(settings.value("handler/databaseFile").toString());

    if(!databaseFile.exists())
    {
        QString fileName = getDatabaseFileName();
        QFile chosenDatabaseFile(fileName);
        if(fileName.isNull() || fileName.isEmpty() || !chosenDatabaseFile.exists())
        {
            return false;
        }
        m_database = Database::Database::instance();
        m_database->initialize(chosenDatabaseFile);
    }
    else
    {
        m_database = Database::Database::instance();
        m_database->initialize(databaseFile);
    }

    //    Database::AtomicRule *before = new Database::AtomicRule();
    //    before->parameter->setValue(QDate::fromString("2010-12-31").toString());
    //    before->attributeName->setValue("date");
    //    before->constraintId->setValue(Database::Constraints::DateIsBefore);

    //    Database::AtomicRule *after = new Database::AtomicRule();
    //    after->parameter->setValue(QDate::fromString("2010-06-01").toString());
    //    after->attributeName->setValue("date");
    //    after->constraintId->setValue(Database::Constraints::DateIsAfter);

    //    Database::RuleConjunction *conjunction = new Database::RuleConjunction();
    //    conjunction->addRule(before);
    //    conjunction->addRule(after);

    //    Database::Rules::instance()->insertRow(conjunction);

    //    foreach(Database::Game *g, Database::Games::instance()->allRows())
    //    {
    //	qDebug() << g->id() << g->date->value();
    //    }

//    foreach(Database::Round* r, Database::Rounds::instance()->allRows())
//    {
//        r->db_state->setValue(r->db_state->value()+1);
//    }

    Server *server = new Server(this);
    server->start();

    m_mainwindow = new Gui::MainWindow::MainWindow();

    m_mainwindow->show();

    return true;
}

Database::Database* Handler::database(){
    return m_database;
}

bool Handler::closeMainWindow()
{
    if(!m_mainwindow.isNull())
    {
        if(m_mainwindow->close())
        {
            if(!m_database.isNull())
            {
                m_database->deleteLater();
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

Gui::MainWindow::MainWindow *Handler::mainWindow() const
{
    return m_mainwindow;
}

QString Handler::getDatabaseFileName()
{
    QSettings settings;
    QString lastOpenFolder = settings.value("handler/lastOpenFolder","~").toString();
    QString fileName = QFileDialog::getOpenFileName(0,
                                                    tr("Choose Database"), lastOpenFolder, tr("Database Files (*.db)"));

    QFile databaseFile(fileName);

    if(databaseFile.exists() || databaseFile.open(QIODevice::WriteOnly))
    {
        settings.setValue("handler/databaseFile",databaseFile.fileName());
        settings.setValue("handler/lastOpenFolder",QFileInfo(databaseFile).absolutePath());
        return databaseFile.fileName();
    }
    else
    {
        return "";
    }
}

int Handler::getDesktopWidth(){
    return QApplication::desktop()->width();
}

int Handler::getDesktopHeight(){
    return QApplication::desktop()->height();
}

MessageSystem* Handler::messageSystem(){
    return m_messagesystem;
}

bool Handler::isMainThread() const
{
    return m_mainThread == QThread::currentThread();
}
