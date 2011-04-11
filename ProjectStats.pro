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
    Database/drink.cpp \
    Database/row.cpp \
    Database/attribute.cpp \
    Database/databaseattribute.cpp \
    Database/samplerow.cpp \
    Database/samplerowchild.cpp \
    Models/tablemodel.cpp \
    Gui/Misc/rowlist.cpp \
    Database/player.cpp

HEADERS  += mainwindow.h \
    Database/table.h \
    Database/database.h \
    singleton.h \
    Database/drink.h \
    Database/row.h \
    Database/attribute.h \
    Database/databaseattribute.h \
    Database/samplerow.h \
    Database/samplerowchild.h \
    Models/tablemodel.h \
    Gui/Misc/rowlist.h \
    Database/player.h

FORMS    += mainwindow.ui
