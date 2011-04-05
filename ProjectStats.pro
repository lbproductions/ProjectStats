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
    Database/database.cpp

HEADERS  += mainwindow.h \
    Database/table.h \
    Database/database.h

FORMS    += mainwindow.ui
