#ifndef HANDLER_H
#define HANDLER_H

#include <QApplication>
#include <QPointer>
#include <QVariant>
#include <QDateTime>

#include <attributevariant.h>

#include <Database/attributehash.h>
#include <Database/attributelist.h>

class MessageSystem;
class QDateTime;

namespace Database
{
    class Database;
    class AttributeBase;
    class Player;
    class Game;
    class LiveGame;
    class Round;
    class ChildCategorie;
    class ParentCategorie;
}


class Updater;

namespace Gui
{
    namespace MainWindow
    {
	class MainWindow;
    }

    namespace Details{
        class AbstractPlayerStatsWidget;
    }
}

//! Der Startpunkt dieses Programms.
/*!
  Hier wird sichergestellt, dass immer nur eine Datenbank und ein MainWindow gleichzeitig geöffnet sind.
  Außerdem wird einfacher Zugriff auf die aktuelle Datenbank gegeben.
  */
class Handler : public QApplication
{
    Q_OBJECT
public:
    /*!
      Initialisiert diese Application
      */
    Handler(int argc, char *argv[]);

    /*!
      Schließt und löscht das MainWindow und die Datenbank.
      */
    ~Handler();

    /*!
      Gibt die eine QApplication Instanz zurück.
      */
    static Handler* const getInstance();


    /*!
      Öffnet eine Datenbank in einem neuen MainWindow. Schließt zuvor ein eventuell geöffnetes anderes Fenster.<br>
      Verwendet die zuletzt geöffnete Datenbank oder fragt den Benutzer nach einer Datenbank, falls eine solche nicht existiert.
      \return true, falls ein neues MainWindow geöffnet wurde.
      */

    bool showMainWindow();

    /*!
      Versucht das aktuelle MainWindow zu schließen. Dazu wird der User gefragt, falls dieser das wünscht.
      \return true, falls nach Ausführung kein MainWindow mehr geöffnet ist.
      */
    bool closeMainWindow();

    /*!
      \return das Message-System-Objekt, das für die Anzeige von Growl-Messages etc. zuständig ist
      */
    MessageSystem* messageSystem();

    /*!
      Gibt die Datenbank zurück, mit der aktuell gearbeitet wird.
      */
    Database::Database* database();

    /*!
      \return Die Auflösungs-Breite des Desktops, auf dem das Programm läuft.
      */
    int getDesktopWidth();

    /*!
      \return Die Auflösungs-Höhe des Desktops, auf dem das Programm läuft.
      */
    int getDesktopHeight();

    /*!
      Checkt im Updater, ob Updates verfügbar sind.
      */
    void checkForUpdates();


    Gui::MainWindow::MainWindow *mainWindow() const;


private:
    /*!
      Fragt den Benutzer nach einer Datenbank, die geöffnet werden soll.
      Hier wird die zuletzt geöffnete Datenbank gespeichert.
      */
    QString getDatabaseFileName();

    QPointer<Database::Database> m_database; //!< Die Datenbank mit der aktuell gearbeitet wird.
    QPointer<Gui::MainWindow::MainWindow> m_mainwindow; //!< Das aktuelle MainWindow
    MessageSystem* m_messagesystem; //! Das MessageSystem-Objekt
    Updater *m_updater;



};

#define COMMA ,

Q_DECLARE_METATYPE(QPointer<Database::Player>)
Q_DECLARE_METATYPE(QPointer<Database::Round>)
Q_DECLARE_METATYPE(QPointer<Database::Game>)
Q_DECLARE_METATYPE(Database::ParentCategorie*)
Q_DECLARE_METATYPE(Database::ChildCategorie*)
Q_DECLARE_METATYPE(QPair<Database::Player* COMMA Database::Player*>)
Q_DECLARE_METATYPE(Database::AttributeHash<Database::LiveGame* COMMA double>)
Q_DECLARE_METATYPE(Database::AttributeHash<Database::Player* COMMA bool>)
Q_DECLARE_METATYPE(Database::AttributeHash<Database::Player* COMMA double>)
Q_DECLARE_METATYPE(Database::AttributeHash<QString COMMA int>)
Q_DECLARE_METATYPE(Database::AttributeHash<QString COMMA double>)
Q_DECLARE_METATYPE(Database::AttributeHash<QString COMMA QDateTime>)
Q_DECLARE_METATYPE(Database::AttributeHash<QPair<Database::Player* COMMA Database::Player*> COMMA int>)
Q_DECLARE_METATYPE(Database::AttributeHash<int COMMA int>)
Q_DECLARE_METATYPE(Database::AttributeHash<QString COMMA Gui::Details::AbstractPlayerStatsWidget*>)
Q_DECLARE_METATYPE(Database::AttributeList<int>)
Q_DECLARE_METATYPE(Database::AttributeList<QString>)
Q_DECLARE_METATYPE(Database::AttributeList<Database::ChildCategorie*>)


#endif // HANDLER_H
