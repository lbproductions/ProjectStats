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

    //    Database::Drink *d = Database::Drinks::instance()->rowById(5);

    //    d->name.setValue("name");
    //    d->type.setValue("type");

    //    QElapsedTimer timer;
    //    timer.start();

    //    qDebug() << "d->test(): " << d->test();
    //    qDebug() << "Took " << timer.elapsed()  << " ms";
    //    timer.restart();

    //    qDebug() << "d->test(): " << d->test();
    //    qDebug() << "Took " << timer.elapsed()  << " ms";
    //    timer.restart();

    //    qDebug() << "d->name.setValue(\"name2\")";
    //    d->name.setValue("name2");
    //    qDebug() << "Took " << timer.elapsed()  << " ms";
    //    timer.restart();

    //    qDebug() << "d->name.setValue(\"name2\")";
    //    d->name.setValue("name2");
    //    qDebug() << "Took " << timer.elapsed()  << " ms";
    //    timer.restart();

    //    qDebug() << "d->test(): " << d->test();
    //    qDebug() << "Took " << timer.elapsed()  << " ms";
    //    timer.restart();

    //    qDebug() << "d->test(): " << d->test();
    //    qDebug() << "Took " << timer.elapsed()  << " ms";
    //    timer.restart();

    //    qDebug() << "d->type.setValue(\"type2\")";
    //    d->type.setValue("type2");
    //    qDebug() << "Took " << timer.elapsed()  << " ms";
    //    timer.restart();

    //    qDebug() << "d->type.setValue(\"type2\")";
    //    d->type.setValue("type2");
    //    qDebug() << "Took " << timer.elapsed()  << " ms";
    //    timer.restart();

    //    qDebug() << "d->test(): " << d->test();
    //    qDebug() << "Took " << timer.elapsed()  << " ms";
    //    timer.restart();

    //    qDebug() << "d->test(): " << d->test();
    //    qDebug() << "Took " << timer.elapsed()  << " ms";
    //    timer.restart();
    return a.exec();
}
