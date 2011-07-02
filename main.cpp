#include <QtGui/QApplication>

#include <Database/Filters/atomicrule.h>
#include <Database/Filters/ruleconjunction.h>
#include <Database/Filters/ruledisjunction.h>
#include <Database/database.h>
#include <Database/listattribute.h>
#include <Database/Calculator/gamecalculator.h>
#include <Database/game.h>

#include <Logger/logger.h>
#include <cocoainitializer.h>

#include <QDebug>
#include <QElapsedTimer>
#include <QThread>

#include <handler.h>

Q_DECLARE_METATYPE(Database::AttributeList<QString>)

int main(int argc, char *argv[])
{
    Logger::init();

#ifdef Q_WS_MAC
    CocoaInitializer cocoaInitializer;
    (void) cocoaInitializer; //supress unused variable warning
#endif

    Handler handler(argc, argv);

    /*Database::Database *database = Database::Database::instance();
    QFile file("/Users/niklaswulf/Dropbox/Public/ProjectStats/projectstats.db");
    database->initialize(file);

    Database::Game *game = Database::Games::instance()->rowById(1);

    Database::ListAttribute<QString,Database::Game, Database::GameCalculator> testAttribute("test","type",game);*/

    //qDebug() << testAttribute.value();

    //handler.installTranslator(&translator);

    if(handler.showMainWindow())
    {
	return handler.exec();
    }
    return 0;
}
