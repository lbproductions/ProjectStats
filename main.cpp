#include <QtGui/QApplication>
#include "mainwindow.h"

#include <Database/database.h>
#include <Database/drinks.h>
#include <Database/drink.h>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Database::Database *database = new Database::Database();
    QFile file("/Users/niklas/Dropbox/Public/ProjectStats/projectstats.db");
    qDebug() << file.exists();
    database->initialize(file);

    foreach( Database::Drink *d, Database::Drinks::instance()->allRows())
    {
        qDebug() << d->id() << ": " << d->name();
    }

    return a.exec();
}
