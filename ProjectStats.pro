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
    Database/Doppelkopf/dokoofflinegamebuddy.cpp \
    Database/categorie.cpp \
    Database/categorieassignment.cpp \
    Database/Filters/ruledisjunction.cpp \
    Database/Filters/ruleconnective.cpp \
    Database/Filters/ruleconjunction.cpp \
    Database/Filters/rule.cpp \
    Database/Filters/atomicrule.cpp \
    Database/Filters/constraints.cpp \
    Database/Calculator/playercalculator.cpp \
    Database/Calculator/placecalculator.cpp \
    Database/Calculator/gamecalculator.cpp \
    Database/Calculator/drinkcalculator.cpp \
    Database/Calculator/livegamecalculator.cpp \
    Database/mappingattribute.cpp \
    Database/attributehash.cpp \
    handler.cpp \
    messagesystem.cpp \
    Database/attributelist.cpp \
    Database/listattribute.cpp \
    global.cpp \
    Database/Calculator/roundcalculator.cpp \
    Database/Calculator/offlinegamecalculator.cpp \
    Database/Calculator/skatlivegamecalculator.cpp \
    Database/Calculator/dokolivegamecalculator.cpp \
    Database/Calculator/dokoroundcalculator.cpp

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
    Database/Doppelkopf/dokoofflinegamebuddy.h \
    Database/categorie.h \
    Database/categorieassignment.h \
    Database/Filters/ruledisjunction.h \
    Database/Filters/ruleconnective.h \
    Database/Filters/ruleconjunction.h \
    Database/Filters/rule.h \
    Database/Filters/atomicrule.h \
    Database/Filters/constraints.h \
    Database/Calculator/playercalculator.h \
    Database/Calculator/placecalculator.h \
    Database/Calculator/gamecalculator.h \
    Database/Calculator/drinkcalculator.h \
    Database/Calculator/livegamecalculator.h \
    Database/mappingattribute.h \
    Database/attributehash.h \
    handler.h \
    messagesystem.h \
    Database/attributelist.h \
    Database/listattribute.h \
    Updater/Updater.h \
    Updater/sparkleupdater.h \
    global.h \
    Database/Calculator/roundcalculator.h \
    Database/Calculator/offlinegamecalculator.h \
    Database/Calculator/skatlivegamecalculator.h \
    Database/Calculator/dokolivegamecalculator.h \
    Database/Calculator/dokoroundcalculator.h

FORMS    +=

mac {
    HEADERS += cocoainitializer.h
    OBJECTIVE_SOURCES += cocoainitializer.mm
    LIBS += -framework AppKit
}

OTHER_FILES += \
    Updater/sparkleupdater.mm \
    Updater/sign_update.rb \
    Updater/rnotes.html \
    Updater/rnotes.css \
    Updater/ProjectStatsAppCast.xml \
    Updater/dsa_pub.pem

RESOURCES += \
    Ressources/Ressources.qrc
