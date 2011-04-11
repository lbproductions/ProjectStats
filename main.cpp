#include <QtGui/QApplication>
#include "mainwindow.h"

#include <Database/database.h>

#include <Logger/logger.h>

#include <QDebug>
#include <QElapsedTimer>
#include <QThread>

int main(int argc, char *argv[])
{
    Logger::init();

    QApplication a(argc, argv);

    Database::Database *database = Database::Database::instance();
    QFile file("/Users/niklas/Dropbox/Public/ProjectStats/projectstats.db");
    database->initialize(file);

    MainWindow w;
    w.show();

    return a.exec();
}
