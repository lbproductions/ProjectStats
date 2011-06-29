#include "handler.h"

/*
#include <Gui/MainWindow/mainwindow.h>
#include <Database/Doppelkopf/dokolivegame.h>

*/

#include <QDebug>
#include <QPointer>
#include <QDesktopWidget>
#include <QSettings>
#include <QFileDialog>

#include <databasewindow.h>
#include <messagesystem.h>
#include <Updater/sparkleupdater.h>
#include <Updater/updater.h>

#include <Database/database.h>
#include <Database/attribute.h>
#include <Database/attributehash.h>
#include <Database/attributelist.h>
#include <Database/player.h>
#include <Database/drink.h>
#include <Database/place.h>
#include <Database/game.h>
#include <Database/round.h>
#include <Database/livegame.h>
#include <Database/Doppelkopf/schmeisserei.h>

Handler::Handler(int argc, char *argv[])
    : QApplication(argc,argv),
      m_updater(0)
{
    setOrganizationName("LB Productions");
    setApplicationName("ProjectStats");

    setAttribute(Qt::AA_DontShowIconsInMenus,true);

    m_messagesystem = new MessageSystem();
    m_messagesystem->showWelcomeMessage();

    this->setWindowIcon(QIcon(":/icons/pslogo"));

#ifdef Q_WS_MAC
    //m_updater = new SparkleUpdater("http://dl.dropbox.com/u/140012/ProjectStats/ProjectStatsAppCast.xml");
#endif

    if (m_updater) {
        m_updater->checkForUpdatesInBackground();
    }
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
}

Handler* const Handler::getInstance(){
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


    m_mainwindow = new DatabaseWindow();

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

DatabaseWindow *Handler::mainWindow() const
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

QVariant Handler::convert(Database::AttributeBase* base, QVariant var){
    QVariant variant;
    if(QString(var.typeName()) == "QPointer<Database::Player>"){
	QPointer<Database::Player> player = base->toVariant().value<QPointer<Database::Player> >();
	if (!player.isNull()){
	    variant.setValue(player->name->value());
	}
    }

    else if(QString(var.typeName()) == "QPointer<Database::Place>"){
	QPointer<Database::Place> place = base->toVariant().value<QPointer<Database::Place> >();
	if (!place.isNull()){
	    variant.setValue(place->strasse->value() + place->nummer->value() + ", " + place->ort->value());
	}
    }

    else if(QString(var.typeName()) == "QPointer<Database::Game>"){
	QPointer<Database::Game> game = base->toVariant().value<QPointer<Database::Game> >();
	if (!game.isNull()){
	    variant.setValue(game->name->value());
	}
    }

    else if(QString(var.typeName()) == "Database::Round*"){
        Database::Round* round = base->toVariant().value<Database::Round*>();
        if (round != 0){
            variant.setValue(round->id());
        }
    }

    else if(QString(var.typeName()) == "Database::Player*"){
        Database::Player* player = base->toVariant().value<Database::Player*>();
        if (player != 0){
            variant.setValue(player->name->value());
        }
    }

    else if(QString(var.typeName()) == "Database::Round::RoundState"){
        Database::Round::RoundState round = base->toVariant().value<Database::Round::RoundState>();
        QPixmap pixmap;
        if(round == Database::Round::FinishedState){
            pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_finished");
            variant.setValue(pixmap);
        }
        else if(round == Database::Round::RunningState){
            pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_running");
            variant.setValue(pixmap);
        }
        else if(round == Database::Round::PausedState){
            pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_paused");
            variant.setValue(pixmap);
        }
        else{
            pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_default");
            variant.setValue(pixmap);
        }

        /*
        switch(round){
            case Database::Round::FinishedState:
                //pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_finished");
                //variant.setValue(pixmap);
                variant.setValue(QString("Finished"));
                break;
            case Database::Round::RunningState:
                pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_running");
                variant.setValue(pixmap);
                 break;
            case Database::Round::PausedState:
                pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_paused");
                variant.setValue(pixmap);
                break;
            default:
                pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_default");
                variant.setValue(pixmap);
                break;
        }
        */
    }

    else if(QString(var.typeName()) == "Database::AttributeList<Database::Place*>"){
	Database::AttributeList<Database::Place*> list = base->toVariant().value<Database::AttributeList<Database::Place*> >();
	QString string = "";
	for (int i = 0; i<list.size();i++){
	    string += list.at(i)->displayString->value();
	    if (i < list.size()-1){
		string += "; ";
	    }
	}
	variant.setValue(string);
    }

    else if(QString(var.typeName()) == "Database::AttributeList<Database::Drink*>"){
        Database::AttributeList<Database::Drink*> list = base->toVariant().value<Database::AttributeList<Database::Drink*> >();
        QHash<Database::Drink*,int> hash;
        for(int i = 0; i<list.size();i++){
            hash.insert(list.at(i),hash.value(list.at(i)) + 1);
        }
        QString string = "";
        for(int i = 0; i<hash.keys().size();i++){
            string += hash.keys().at(i)->name->value() + " (" + QString::number(hash.value(hash.keys().at(i))) + ")";
            if (i < hash.keys().size()-1){
                string += "; ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(var.typeName()) == "Database::AttributeList<Database::Game*>"){
	Database::AttributeList<Database::Game*> list = base->toVariant().value<Database::AttributeList<Database::Game*> >();
	variant.setValue(list.size());
    }

    else if(QString(var.typeName()) == "Database::AttributeList<Database::Round*>"){
        Database::AttributeList<Database::Round*> list = base->toVariant().value<Database::AttributeList<Database::Round*> >();
        variant.setValue(list.size());
    }

    else if(QString(var.typeName()) == "Database::AttributeList<Database::Player*>"){
	Database::AttributeList<Database::Player*> list = base->toVariant().value<Database::AttributeList<Database::Player*> >();
	QString string = "";
	for (int i = 0; i<list.size();i++){
	    string += list.at(i)->name->value();
	    if (i < list.size()-1){
		string += ", ";
	    }
	}
	variant.setValue(string);
    }

    else if(QString(var.typeName()) == "Database::AttributeList<Database::Schmeisserei*>"){
        Database::AttributeList<Database::Schmeisserei*> list = base->toVariant().value<Database::AttributeList<Database::Schmeisserei*> >();
        QString string = "";
        for (int i = 0; i<list.size();i++){
            string += list.at(i)->player->value()->name->value();
            string += ":";
            string += list.at(i)->type->value();
            if (i < list.size()-1){
                string += ", ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(var.typeName()) == "Database::AttributeHash<Database::Player*COMMA int>"){
	QString string = "";
	Database::AttributeHash<Database::Player*,int> hash = base->toVariant().value<Database::AttributeHash<Database::Player*,int> >();
	foreach(Database::Player* p, hash.keys()){
            string += p->name->value() + ":" + QString::number(hash.value(p)) + ", ";
	}
	variant.setValue(string);
    }

    else if(QString(var.typeName()) == "Database::AttributeHash<Database::Player*COMMA double>"){
        QString string = "";
        Database::AttributeHash<Database::Player*,double> hash = base->toVariant().value<Database::AttributeHash<Database::Player*,double> >();
        foreach(Database::Player* p, hash.keys()){
            string += p->name->value() + ":" + QString::number(hash.value(p)) + ", ";
        }
        variant.setValue(string);
    }

    else if(QString(var.typeName()) == "Database::AttributeHash<Database::Player*COMMA bool>"){
        QString string = "";
        Database::AttributeHash<Database::Player*,bool> hash = base->toVariant().value<Database::AttributeHash<Database::Player*,bool> >();
        foreach(Database::Player* p, hash.keys()){
            if(hash.value(p)){
                string += p->name->value() + ":" + "true" + ", ";
            }
            else{
                string += p->name->value() + ":" + "false" + ", ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(var.typeName()) == "Database::AttributeHash<Database::LiveGame*COMMA double>"){
        QString string = "";
        Database::AttributeHash<Database::LiveGame*,double> hash = base->toVariant().value<Database::AttributeHash<Database::LiveGame*,double> >();
        foreach(Database::LiveGame* p, hash.keys()){
            string += p->name->value() + ":" + QString::number(hash.value(p)) + ", ";
        }
        variant.setValue(string);
    }
    else if(QString(var.typeName()) == "Database::AttributeHash<QString COMMA int>"){
        QString string = "";
        Database::AttributeHash<QString,int> hash = base->toVariant().value<Database::AttributeHash<QString,int> >();
        foreach(QString i, hash.keys()){
            string += i + ":" + QString::number(hash.value(i)) + ", ";
        }
        variant.setValue(string);
    }
    else if(QString(var.typeName()) == "Database::AttributeHash<int COMMA int>"){
        QString string = "";
        Database::AttributeHash<int,int> hash = base->toVariant().value<Database::AttributeHash<int,int> >();
        foreach(int i, hash.keys()){
            string += QString::number(i) + ":" + QString::number(hash.value(i)) + ", ";
        }
        variant.setValue(string);
    }
    else if(QString(var.typeName()) == "Database::AttributeHash<QPair<Database::Player*COMMA Database::Player*>COMMA int>"){
        QString string = "";
        Database::AttributeHash<QPair<Database::Player*,Database::Player*>,int> hash = base->toVariant().value<Database::AttributeHash<QPair<Database::Player*,Database::Player*>,int> >();
        for(int i = 0; i< hash.keys().size();i++){
            QPair<Database::Player*,Database::Player*> pair = hash.keys().at(i);
            string += pair.first->name->value() + "-" + pair.second->name->value() + ":" + QString::number(hash.value(pair)) + " ,";
        }
        variant.setValue(string);
    }


    return variant;
}
