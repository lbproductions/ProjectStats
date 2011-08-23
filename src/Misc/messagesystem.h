#ifndef MESSAGESYSTEM_H
#define MESSAGESYSTEM_H

 #include <QSystemTrayIcon>
 #include <QObject>

namespace Database{

    class LiveGame;

}

class MessageSystem: public QObject
{
    Q_OBJECT
public:
    MessageSystem();

    void registerAtGrowl();

    void showWelcomeMessage();

    void showWarning(QString title, QString message);

    void showMessage(QString title, QString message, QString avatarpath);

    //void checkForStats(Database::LiveGame* livegame);

private:
    QSystemTrayIcon* m_message;
};

#endif // MESSAGESYSTEM_H
