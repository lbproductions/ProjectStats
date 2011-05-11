#include <QtGui/QApplication>
#include "mainwindow.h"

#include <Database/database.h>

#include <Logger/logger.h>
#include <cocoainitializer.h>

#include <QDebug>
#include <QElapsedTimer>
#include <QThread>

#include <handler.h>

int main(int argc, char *argv[])
{
    Logger::init();

#ifdef Q_WS_MAC
    CocoaInitializer cocoaInitializer;
    (void) cocoaInitializer; //supress unused variable warning
#endif

    Handler handler(argc, argv);

    Database::Database *database = Database::Database::instance();
    QFile file("/Users/niclasraabe/Dropbox/Public/projectstats.db");
    database->initialize(file);

    MainWindow w;
    w.show();

    //handler.installTranslator(&translator);

    if(handler.showMainWindow())
    {
        //Adapter* adapter = new Adapter("/dortmund2.bin");
        return handler.exec();
    }
    return 0;
}
