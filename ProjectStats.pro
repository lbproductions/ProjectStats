#-------------------------------------------------
#
# Project created by QtCreator 2011-04-05T17:37:03
#
#-------------------------------------------------

QT       += core gui sql

TARGET = ProjectStats
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Database/table.cpp \
    Database/database.cpp \
    singleton.cpp \
    Database/drinks.cpp \
    Database/drink.cpp \
    Database/row.cpp

HEADERS  += mainwindow.h \
    Database/table.h \
    Database/database.h \
    singleton.h \
    Database/drinks.h \
    Database/drink.h \
    Database/row.h

FORMS    += mainwindow.ui
