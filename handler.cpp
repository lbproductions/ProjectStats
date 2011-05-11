#include "handler.h"

/*

#include <Database/database.h>
#include <Gui/MainWindow/mainwindow.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Updater/sparkleupdater.h>
#include <Updater/updater.h>
#include <Stats/stats.h>

#include <QDebug>
#include <QSettings>
#include <QFileDialog>
#include <QDesktopWidget>

*/

#include <QDebug>
#include <QPointer>

#include <mainwindow.h>
#include <messagesystem.h>

#include <Database/attribute.h>
#include <Database/attributehash.h>
#include <Database/attributelist.h>
#include <Database/player.h>
#include <Database/drink.h>
#include <Database/place.h>
#include <Database/game.h>

Handler::Handler(int argc, char *argv[])
    : QApplication(argc,argv)
    //m_updater(0)
{
    setOrganizationName("LB Productions");
    setApplicationName("ProjectStats");

    setAttribute(Qt::AA_DontShowIconsInMenus,true);

    m_messagesystem = new MessageSystem();

    /*

    this->setWindowIcon(QIcon(":/icons/pslogo"));

#ifdef Q_WS_MAC
    m_updater = new SparkleUpdater("http://dl.dropbox.com/u/140012/ProjectStats/ProjectStatsAppCast.xml");
#endif

    if (m_updater) {
      m_updater->checkForUpdatesInBackground();
    }

    m_stats = new Stats::Stats();

    */
}

Handler::~Handler()
{
    /*
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
    */
}

Handler* const Handler::getInstance(){
    return qobject_cast<Handler*>(QApplication::instance());
}

/*

void Handler::checkForUpdates()
{
    if (m_updater) {
      m_updater->checkForUpdates();
    }
}

*/
bool Handler::showMainWindow(){

    /*
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
 m_database = new Database::Database(chosenDatabaseFile,this);
    }
    else
    {
 m_database = new Database::Database(databaseFile,this);
    }

    */
    m_mainwindow = new MainWindow();

    m_mainwindow->show();
    return true;
}

/*
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

Database::Database* Handler::database(){
    return m_database;
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

Stats::Stats* Handler::stats(){
    return m_stats;
}

int Handler::getDesktopWidth(){
    return QApplication::desktop()->width();
}

int Handler::getDesktopHeight(){
    return QApplication::desktop()->height();
}

*/

MessageSystem* Handler::messageSystem(){
    return m_messagesystem;
}

QVariant Handler::convert(Database::AttributeBase* base, QVariant var){
    QVariant variant;

    if(QString(var.typeName()) == "QList<Database::Drink*>"){
        QList<Database::Drink*> list = base->toVariant().value<QList<Database::Drink*> >();
        QString string = "";
        for (int i = 0; i<list.size();i++){
            string += list.at(i)->name->value();
            if (i < list.size()-1){
                string += ", ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(var.typeName()) == "QPointer<Database::Player>"){
        QPointer<Database::Player> player = base->toVariant().value<QPointer<Database::Player> >();
        if (!player.isNull()){
            variant.setValue(player->name->value());
        }
    }

    else if(QString(var.typeName()) == "Database::AttributeList<Database::Place*>*"){
        Database::AttributeList<Database::Place*>* list = base->toVariant().value<Database::AttributeList<Database::Place*>* >();
        QString string = "";
        for (int i = 0; i<list->size();i++){
            string += list->at(i)->displayString->value();
            if (i < list->size()-1){
                string += "; ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(var.typeName()) == "Database::AttributeList<Database::Game*>*"){
        Database::AttributeList<Database::Game*>* list = base->toVariant().value<Database::AttributeList<Database::Game*>* >();
        variant.setValue(list->size());
    }

    else if(QString(var.typeName()) == "QPointer<Database::Place>"){
        QPointer<Database::Place> place = base->toVariant().value<QPointer<Database::Place> >();
        if (!place.isNull()){
            variant.setValue(place->strasse->value() + place->nummer->value() + ", " + place->ort->value());
        }
    }

    else if(QString(var.typeName()) == "QList<Database::Player*>"){
        QList<Database::Player*> list = base->toVariant().value<QList<Database::Player*> >();
        QString string = "";
        for (int i = 0; i<list.size();i++){
            string += list.at(i)->name->value();
            if (i < list.size()-1){
                string += ", ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(var.typeName()) == "Database::AttributeHash<Database::Player*COMMA int>*"){
        QString string = "";
        Database::AttributeHash<Database::Player*,int>* hash = base->toVariant().value<Database::AttributeHash<Database::Player*,int>* >();
        foreach(Database::Player* p, hash->keys()){
            string += p->name->value() + ":" + QString::number(hash->value(p)) + ", ";
        }
        variant.setValue(string);
    }

    else if(QString(var.typeName()) == "QPointer<Database::Game>"){
        QPointer<Database::Game> game = base->toVariant().value<QPointer<Database::Game> >();
        if (!game.isNull()){
            variant.setValue(game->name->value());
        }
    }
    else if(QString(var.typeName()) == "Database::AttributeList<Database::Player*>*"){
        Database::AttributeList<Database::Player*>* list = base->toVariant().value<Database::AttributeList<Database::Player*>* >();
        QString string = "";
        for (int i = 0; i<list->size();i++){
            string += list->at(i)->name->value();
            if (i < list->size()-1){
                string += ", ";
            }
        }
        variant.setValue(string);
    }


    return variant;
}
