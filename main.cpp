#include <QtGui/QApplication>

#include <Logger/logger.h>
#include <cocoainitializer.h>
#include <handler.h>

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
