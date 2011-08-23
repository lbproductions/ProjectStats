#include "messagesystem.h"

#include <Database/player.h>
#include <Database/livegame.h>

#include <QProcess>
#include <QDebug>
#include <QDir>

MessageSystem::MessageSystem()
{
    m_message = new QSystemTrayIcon();

#ifdef Q_WS_MAC
    registerAtGrowl();
#endif

}

void MessageSystem::registerAtGrowl(){
    QString aScript =
                "tell application \"GrowlHelperApp\"\n"
                "	set the allNotificationsList to ¬\n"
                "		{\"Error\", \"Stats\", \"Notification\"}\n"
                "	set the enabledNotificationsList to ¬\n"
                "		{\"Error\", \"Stats\", \"Notification\"}\n"
                "	register as application ¬\n"
                "		\"ProjectStats\" all notifications allNotificationsList ¬\n"
                "		default notifications enabledNotificationsList ¬\n"
                "		icon of application \"ProjectStats\"\n"
                "end tell\n";

        QString osascript = "/usr/bin/osascript";
        QStringList processArguments;
        processArguments << "-l" << "AppleScript";

        QProcess p;
        p.start(osascript, processArguments);
        p.write(aScript.toAscii());
        p.closeWriteChannel();
        p.waitForFinished();
}

void MessageSystem::showWelcomeMessage(){
    //m_message->show();
    //m_message->showMessage("Welcome","Welcome to ProjectStats! The world of Doko and other cardgames.",QSystemTrayIcon::Information,1000);

    QString aScript =
                "tell application \"GrowlHelperApp\"\n"
                "   notify with name ¬\n"
                "       \"Notification\" title ¬\n"
                "       \"Welcome\" description ¬\n"
                "       \"Welcome to ProjectStats! The world of Doko and other cardgames.\" application name \"ProjectStats\" image from location ¬\n"
                "       \"" + QDir("./../../../../").absolutePath() + "/trunk/Ressources/graphics/icons/general/ProjectStats_logo.png\"\n"
                "end tell\n";

        QString osascript = "/usr/bin/osascript";
        QStringList processArguments;
        processArguments << "-l" << "AppleScript";

        QProcess p;
        p.start(osascript, processArguments);
        p.write(aScript.toAscii());
        p.closeWriteChannel();
        p.waitForFinished();
}

void MessageSystem::showWarning(QString title, QString message){
    m_message->show();
    m_message->showMessage(title,message,QSystemTrayIcon::Warning,1000);
}

void MessageSystem::showMessage(QString title, QString message, QString avatarpath){
    //m_message->show();
    //m_message->setIcon(icon);
    //m_message->showMessage(title,message,QSystemTrayIcon::Information,2000);

    QString aScript =
                "tell application \"GrowlHelperApp\"\n"
                "   notify with name ¬\n"
                "       \"Notification\" title ¬\n"
                "       " + title +" description ¬\n"
                "       " + message +" application name \"ProjectStats\" image from location ¬\n"
                "       " + avatarpath + "\n"
                "end tell\n";

        QString osascript = "/usr/bin/osascript";
        QStringList processArguments;
        processArguments << "-l" << "AppleScript";

        QProcess p;
        p.start(osascript, processArguments);
        p.write(aScript.toAscii());
        p.closeWriteChannel();
        p.waitForFinished();
}

/*
void MessageSystem::checkForStats(Database::LiveGame* livegame){
    if (livegame->rounds().size() == 1){
       foreach(Database::Player* p, livegame->playersSortedByPlacement()){
            if (p->games().size()%25 == 0){
                showMessage(QString::number(p->games().size())+tr(". game"),
                                                                     p->name() + tr(" is playing his ") + QString::number(p->games().size()) + tr(". game."),p->avatarFilePath());
            }
            if ((p->stats().value(livegame->type())->games()+1)%25 == 0){
                showMessage(QString::number(p->stats().value(livegame->type())->games()+1)+". " + livegame->type() + tr("-Game"),
                                                                     p->name() + tr(" is playing his ") + QString::number(p->stats().value(livegame->type())->games()+1) + tr(". game."),p->avatarFilePath());
            }
       }
    }
    if(livegame->isFinished()){
        Database::Player* p = livegame->playersSortedByPlacement().at(0);
        if (p->generalStats()->wins()%25 == 0){
            showMessage(QString::number(p->generalStats()->wins())+tr(". win"),
                                                                 p->name() + tr(" has won his ") + QString::number(p->generalStats()->wins()) + tr(". game."),p->avatarFilePath());
        }
    }
}
*/
