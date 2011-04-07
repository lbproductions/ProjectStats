#include <QtGui/QApplication>
#include "mainwindow.h"

#include <Database/database.h>
#include <Database/drinks.h>
#include <Database/drink.h>

#include <QDebug>
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database::Database *database = Database::Database::instance();
    QFile file("/Users/niklas/Dropbox/Public/ProjectStats/projectstats.db");
    database->initialize(file);

    MainWindow w;
    w.show();

    return a.exec();
}
