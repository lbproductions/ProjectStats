#-------------------------------------------------
#
# Project created by QtCreator 2011-04-05T17:37:03
#
#-------------------------------------------------

QT       += core gui sql webkit network xml

TARGET = ProjectStats
TEMPLATE = app


SOURCES += main.cpp\
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
    Database/Calculator/dokoroundcalculator.cpp \
    databasewindow.cpp \
    Gui/MainWindow/toolbar.cpp \
    Gui/MainWindow/statusbarbutton.cpp \
    Gui/MainWindow/statusbar.cpp \
    Gui/MainWindow/menubar.cpp \
    Gui/MainWindow/mainwindow.cpp \
    Gui/MainWindow/actionsmanager.cpp \
    Gui/MainWindow/Sidebar/sidebartreeview.cpp \
    Gui/MainWindow/Sidebar/sidebarstatusbardragbutton.cpp \
    Gui/MainWindow/Sidebar/sidebarstatusbar.cpp \
    Gui/MainWindow/Sidebar/sidebaritemdelegate.cpp \
    Gui/MainWindow/Sidebar/sidebar.cpp \
    Gui/MainWindow/Views/view.cpp \
    Gui/MainWindow/Views/ListView/listview.cpp \
    Gui/Details/PlaceDetails/placedetailswidget.cpp \
    Gui/Details/PlaceDetails/googlemap.cpp \
    Gui/Details/GameDetails/gamesummarywidget.cpp \
    Gui/Details/GameDetails/gamedetailswidget.cpp \
    Gui/Details/DrinkDetails/DrinkDetailsWidget.cpp \
    Gui/Details/detailswidget.cpp \
    Gui/Filter/newleaguedialog.cpp \
    Gui/Filter/changematchdaybar.cpp \
    Gui/Misc/valuelabel.cpp \
    Gui/Misc/splitter.cpp \
    Gui/Misc/psprogressbar.cpp \
    Gui/Misc/progressinfoboxwidget.cpp \
    Gui/Misc/placescombobox.cpp \
    Gui/Misc/newrowwidget.cpp \
    Gui/Misc/headerlabel.cpp \
    Gui/Misc/draggablelabel.cpp \
    Gui/Misc/clickablelabel.cpp \
    Database/Categories/playersfoldercategorie.cpp \
    Database/Categories/playerscategorie.cpp \
    Database/Categories/placesfoldercategorie.cpp \
    Database/Categories/placescategorie.cpp \
    Database/Categories/parentcategorie.cpp \
    Database/Categories/gamesfoldercategorie.cpp \
    Database/Categories/gamescategorie.cpp \
    Database/Categories/foldercategorie.cpp \
    Database/Categories/drinksfoldercategorie.cpp \
    Database/Categories/drinkscategorie.cpp \
    Database/Categories/childcategorie.cpp \
    Models/categoriesmodel.cpp \
    Gui/Details/statswidget.cpp \
    Gui/Details/rowwindow.cpp \
    Gui/Details/rowwidget.cpp \
    Gui/Details/summarywidget.cpp \
    Gui/Misc/rowlistheader.cpp

HEADERS  += \
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
    Database/Calculator/dokoroundcalculator.h \
    databasewindow.h \
    Gui/MainWindow/toolbar.h \
    Gui/MainWindow/statusbarbutton.h \
    Gui/MainWindow/statusbar.h \
    Gui/MainWindow/menubar.h \
    Gui/MainWindow/mainwindow.h \
    Gui/MainWindow/actionsmanager.h \
    Gui/MainWindow/Sidebar/sidebartreeview.h \
    Gui/MainWindow/Sidebar/sidebarstatusbardragbutton.h \
    Gui/MainWindow/Sidebar/sidebarstatusbar.h \
    Gui/MainWindow/Sidebar/sidebaritemdelegate.h \
    Gui/MainWindow/Sidebar/sidebar.h \
    Gui/MainWindow/Views/view.h \
    Gui/MainWindow/Views/ListView/listview.h \
    Gui/Details/PlaceDetails/placedetailswidget.h \
    Gui/Details/PlaceDetails/googlemap.h \
    Gui/Details/GameDetails/gamesummarywidget.h \
    Gui/Details/GameDetails/gamedetailswidget.h \
    Gui/Details/DrinkDetails/DrinkDetailsWidget.h \
    Gui/Details/detailswidget.h \
    Gui/Filter/newleaguedialog.h \
    Gui/Filter/changematchdaybar.h \
    Gui/Misc/valuelabel.h \
    Gui/Misc/splitter.h \
    Gui/Misc/psprogressbar.h \
    Gui/Misc/progressinfoboxwidget.h \
    Gui/Misc/placescombobox.h \
    Gui/Misc/newrowwidget.h \
    Gui/Misc/headerlabel.h \
    Gui/Misc/draggablelabel.h \
    Gui/Misc/clickablelabel.h \
    Database/Categories/playersfoldercategorie.h \
    Database/Categories/playerscategorie.h \
    Database/Categories/placesfoldercategorie.h \
    Database/Categories/placescategorie.h \
    Database/Categories/parentcategorie.h \
    Database/Categories/gamesfoldercategorie.h \
    Database/Categories/gamescategorie.h \
    Database/Categories/foldercategorie.h \
    Database/Categories/drinksfoldercategorie.h \
    Database/Categories/drinkscategorie.h \
    Database/Categories/childcategorie.h \
    Models/categoriesmodel.h \
    Database/Filters/rules.h \
    Gui/Misc/macwindowcontroller.h \
    Gui/Details/statswidget.h \
    Gui/Details/rowwindow.h \
    Gui/Details/rowwidget.h \
    Gui/Details/summarywidget.h \
    Gui/Misc/rowlistheader.h

FORMS    += \
    Gui/Details/PlaceDetails/placedetailswidget.ui \
    Gui/Details/GameDetails/gamesummarywidget.ui \
    Gui/Details/GameDetails/gamedetailswidget.ui \
    Gui/Details/DrinkDetails/DrinkDetailsWidget.ui \
    Gui/Filter/newleaguedialog.ui \
    Gui/Misc/newrowwidget.ui

mac {
    HEADERS += cocoainitializer.h
    OBJECTIVE_SOURCES += cocoainitializer.mm \
                        Gui/Misc/macwindowcontroller.mm
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
