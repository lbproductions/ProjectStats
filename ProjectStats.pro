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
    Database/player.cpp \
    Database/place.cpp \
    Database/game.cpp \
    Database/round.cpp \
    Logger/logger.cpp \
    Database/livegame.cpp \
    Database/offlinegame.cpp \
    Database/Doppelkopf/dokolivegame.cpp \
    Database/Skat/skatlivegame.cpp \
    Database/Doppelkopf/dokoround.cpp \
    Database/Skat/skatround.cpp \
    Database/point.cpp \
    Database/position.cpp \
    Database/Doppelkopf/dokoofflinegame.cpp \
    Database/offlinegameinformation.cpp \
    Database/Doppelkopf/dokoofflinegameinformation.cpp \
    Database/livegamedrink.cpp \
    Database/Doppelkopf/schmeisserei.cpp \
    Database/Doppelkopf/dokoofflinegamebuddy.cpp

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
    Database/player.h \
    Database/place.h \
    Database/game.h \
    Database/round.h \
    Logger/logger.h \
    Database/livegame.h \
    Database/offlinegame.h \
    Database/Doppelkopf/dokolivegame.h \
    Database/Skat/skatlivegame.h \
    Database/Doppelkopf/dokoround.h \
    Database/Skat/skatround.h \
    Database/point.h \
    Database/position.h \
    Database/Doppelkopf/dokoofflinegame.h \
    Database/offlinegameinformation.h \
    Database/Doppelkopf/dokoofflinegameinformation.h \
    Database/livegamedrink.h \
    Database/Doppelkopf/schmeisserei.h \
    Database/Doppelkopf/dokoofflinegamebuddy.h

FORMS    +=

mac {
    HEADERS += cocoainitializer.h
    OBJECTIVE_SOURCES += cocoainitializer.mm
    LIBS += -framework AppKit
}
