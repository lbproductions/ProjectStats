#-------------------------------------------------
#
# Project created by QtCreator 2011-04-05T17:37:03
#
#-------------------------------------------------

QT          += core gui sql webkit network xml
TARGET      = ProjectStats
TEMPLATE    = app

DESTDIR     = $PWD/../
DEFINES     += WITH_NONAMESPACES # needed for gsoap

SOURCES += main.cpp\
    Misc/singleton.cpp \
    Database/drink.cpp \
    Gui/Misc/rowlist.cpp \
    Database/player.cpp \
    Database/place.cpp \
    Database/game.cpp \
    Database/round.cpp \
    Misc/logger.cpp \
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
    Misc/handler.cpp \
    Misc/messagesystem.cpp \
    Misc/global.cpp \
    Database/Calculator/roundcalculator.cpp \
    Database/Calculator/offlinegamecalculator.cpp \
    Database/Calculator/skatlivegamecalculator.cpp \
    Database/Calculator/dokolivegamecalculator.cpp \
    Database/Calculator/dokoroundcalculator.cpp \
    Gui/Misc/databasewindow.cpp \
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
    Gui/Misc/rowlistheader.cpp \
    Gui/Wizards/NewGame/wizardsidewidget.cpp \
    Gui/Wizards/NewGame/skatlivegameoptionswidget.cpp \
    Gui/Wizards/NewGame/offlinesummarywidget.cpp \
    Gui/Wizards/NewGame/offlinegameresultwidget.cpp \
    Gui/Wizards/NewGame/offlinegameoptionswidget.cpp \
    Gui/Wizards/NewGame/offlinedetailledgamedokowidget.cpp \
    Gui/Wizards/NewGame/newgamewizard.cpp \
    Gui/Wizards/NewGame/liveofflinegamewidget.cpp \
    Gui/Wizards/NewGame/livegamegeneraloptionswidget.cpp \
    Gui/Wizards/NewGame/livedokogameoptionswidget.cpp \
    Gui/Details/LiveGameDetails/livegamesettingswidget.cpp \
    Gui/Details/LiveGameDetails/livegamerowwindow.cpp \
    Gui/Details/LiveGameDetails/livegameroundtable.cpp \
    Gui/Details/LiveGameDetails/livegameinfogroupbox.cpp \
    Gui/Details/LiveGameDetails/livegamedetailswidget.cpp \
    Gui/Details/LiveGameDetails/endlivegamewidget.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/schmeissereiwidget.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/newdokoroundwidget.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamerowwindow.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameroundtable.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameplayerstatswidget.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameinfogroupbox.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamedetailswidget.cpp \
    Gui/Details/LiveGameDetails/choosedrinkcountdialog.cpp \
    Gui/Details/LiveGameDetails/beerwidget.cpp \
    Gui/Details/LiveGameDetails/beerplayerwidget.cpp \
    Gui/Details/LiveGameDetails/adddrinkwidget.cpp \
    Gui/Graphs/livegamegraphview.cpp \
    Gui/Graphs/Items/livegameplayerpointsgraph.cpp \
    Gui/Graphs/Items/livegamecoordinatesystem.cpp \
    Gui/Graphs/Items/graphpoint.cpp \
    Gui/Graphs/Items/graph.cpp \
    Gui/Graphs/Items/dokolivegameplayerpointsgraph.cpp \
    Gui/Graphs/Items/dokolivegamecoordinatesystem.cpp \
    Gui/Graphs/Items/dokographpoint.cpp \
    Gui/Graphs/Items/coordinatesystem.cpp \
    Gui/Graphs/Items/abstractitem.cpp \
    Gui/Graphs/graphview.cpp \
    Gui/Graphs/dokolivegamegraphview.cpp \
    Gui/Details/PlayerDetails/playerdetailswidget.cpp \
    Gui/Details/PlayerDetails/playerstatswidget.cpp \
    Gui/Details/LiveGameDetails/abstractlivegamewidget.cpp \
    Gui/Details/PlayerDetails/abstractplayerstatswidget.cpp \
    Database/Doppelkopf/dokoplayerstats.cpp \
    Gui/Details/PlayerDetails/dokoplayerstatswidget.cpp \
    Gui/Details/LiveGameDetails/livegamesummarywidget.cpp \
    Database/Categories/leaguefoldercategorie.cpp \
    Database/Filters/enoughleagueplayersrule.cpp \
    Gui/MainWindow/Views/LeagueView/leagueview.cpp \
    Gui/MainWindow/Views/LeagueView/leaguestatswidget.cpp \
    Gui/MainWindow/Views/LeagueView/leagueoverviewwidget.cpp \
    Gui/MainWindow/Views/LeagueView/leaguegraphwidget.cpp \
    Gui/Misc/groupbox.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameroundtableitem.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameroundtabledelegate.cpp \
    Database/playerplaceassignment.cpp \
    Gui/Details/PlayerDetails/playerresidencewidget.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/dokoendlivegamewidget.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamesummarywidget.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/newdoppelkopfroundwidget.cpp \
    Gui/Misc/checkbox.cpp \
    Gui/Misc/playercheckbox.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/NewDokoRoundWidget/column.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/NewDokoRoundWidget/recolumn.cpp \
    Gui/Details/LiveGameDetails/Doppelkopf/NewDokoRoundWidget/hochzeitcolumn.cpp \
    Server/soapprojectstatsService.cpp \
    Server/soapprojectstatsProxy.cpp \
    Server/soapC.cpp \
    Server/stdsoap2.cpp \
    Server/server.cpp \
    Gui/Misc/sheet.cpp \
    Database/Categories/smartfoldercategorie.cpp \
    Database/Filters/leaguerule.cpp

HEADERS  += \
    Misc/singleton.h \
    Database/drink.h \
    Gui/Misc/rowlist.h \
    Database/player.h \
    Database/place.h \
    Database/game.h \
    Database/round.h \
    Misc/logger.h \
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
    Misc/handler.h \
    Misc/messagesystem.h \
    Misc/Updater/Updater.h \
    Misc/global.h \
    Database/Calculator/roundcalculator.h \
    Database/Calculator/offlinegamecalculator.h \
    Database/Calculator/skatlivegamecalculator.h \
    Database/Calculator/dokolivegamecalculator.h \
    Database/Calculator/dokoroundcalculator.h \
    Gui/Misc/databasewindow.h \
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
    Gui/Misc/rowlistheader.h \
    Gui/Wizards/NewGame/wizardsidewidget.h \
    Gui/Wizards/NewGame/skatlivegameoptionswidget.h \
    Gui/Wizards/NewGame/offlinesummarywidget.h \
    Gui/Wizards/NewGame/offlinegameresultwidget.h \
    Gui/Wizards/NewGame/offlinegameoptionswidget.h \
    Gui/Wizards/NewGame/offlinedetailledgamedokowidget.h \
    Gui/Wizards/NewGame/newgamewizard.h \
    Gui/Wizards/NewGame/liveofflinegamewidget.h \
    Gui/Wizards/NewGame/livegamegeneraloptionswidget.h \
    Gui/Wizards/NewGame/livedokogameoptionswidget.h \
    Gui/Details/LiveGameDetails/livegamesettingswidget.h \
    Gui/Details/LiveGameDetails/livegamerowwindow.h \
    Gui/Details/LiveGameDetails/livegameroundtable.h \
    Gui/Details/LiveGameDetails/livegameinfogroupbox.h \
    Gui/Details/LiveGameDetails/livegamedetailswidget.h \
    Gui/Details/LiveGameDetails/endlivegamewidget.h \
    Gui/Details/LiveGameDetails/Doppelkopf/schmeissereiwidget.h \
    Gui/Details/LiveGameDetails/Doppelkopf/newdokoroundwidget.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamerowwindow.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameroundtable.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameplayerstatswidget.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameinfogroupbox.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamedetailswidget.h \
    Gui/Details/LiveGameDetails/choosedrinkcountdialog.h \
    Gui/Details/LiveGameDetails/beerwidget.h \
    Gui/Details/LiveGameDetails/beerplayerwidget.h \
    Gui/Details/LiveGameDetails/adddrinkwidget.h \
    Gui/Graphs/roundgraphview.h \
    Gui/Graphs/livegamegraphview.h \
    Gui/Graphs/Items/playergraph.h \
    Gui/Graphs/Items/livegameplayerpointsgraph.h \
    Gui/Graphs/Items/livegamecoordinatesystem.h \
    Gui/Graphs/Items/graphpoint.h \
    Gui/Graphs/Items/graph.h \
    Gui/Graphs/Items/dokolivegameplayerpointsgraph.h \
    Gui/Graphs/Items/dokolivegamecoordinatesystem.h \
    Gui/Graphs/Items/dokographpoint.h \
    Gui/Graphs/Items/coordinatesystem.h \
    Gui/Graphs/Items/abstractitem.h \
    Gui/Graphs/graphview.h \
    Gui/Graphs/dokolivegamegraphview.h \
    Gui/Details/PlayerDetails/playerdetailswidget.h \
    Gui/Details/PlayerDetails/playerstatswidget.h \
    Gui/Details/LiveGameDetails/livegamesettingswidget.h \
    Gui/Details/LiveGameDetails/livegamerowwindow.h \
    Gui/Details/LiveGameDetails/livegameroundtable.h \
    Gui/Details/LiveGameDetails/livegameinfogroupbox.h \
    Gui/Details/LiveGameDetails/livegamedetailswidget.h \
    Gui/Details/LiveGameDetails/endlivegamewidget.h \
    Gui/Details/LiveGameDetails/Doppelkopf/schmeissereiwidget.h \
    Gui/Details/LiveGameDetails/Doppelkopf/newdokoroundwidget.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamerowwindow.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameroundtable.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameplayerstatswidget.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameinfogroupbox.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamedetailswidget.h \
    Gui/Details/LiveGameDetails/choosedrinkcountdialog.h \
    Gui/Details/LiveGameDetails/beerwidget.h \
    Gui/Details/LiveGameDetails/beerplayerwidget.h \
    Gui/Details/LiveGameDetails/adddrinkwidget.h \
    Gui/Details/LiveGameDetails/abstractlivegamewidget.h \
    Gui/Details/PlayerDetails/abstractplayerstatswidget.h \
    Database/Doppelkopf/dokoplayerstats.h \
    Gui/Details/PlayerDetails/dokoplayerstatswidget.h \
    Gui/Details/LiveGameDetails/livegamesummarywidget.h \
    Database/Categories/leaguefoldercategorie.h \
    Database/Filters/enoughleagueplayersrule.h \
    Gui/MainWindow/Views/LeagueView/leagueview.h \
    Gui/MainWindow/Views/LeagueView/leaguestatswidget.h \
    Gui/MainWindow/Views/LeagueView/leagueoverviewwidget.h \
    Gui/MainWindow/Views/LeagueView/leaguegraphwidget.h \
    Gui/Misc/groupbox.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameroundtableitem.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameroundtabledelegate.h \
    Database/playerplaceassignment.h \
    Gui/Details/PlayerDetails/playerresidencewidget.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokoendlivegamewidget.h \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamesummarywidget.h \
    Gui/Details/LiveGameDetails/Doppelkopf/newdoppelkopfroundwidget.h \
    Gui/Misc/checkbox.h \
    Gui/Misc/playercheckbox.h \
    Gui/Details/LiveGameDetails/Doppelkopf/NewDokoRoundWidget/column.h \
    Gui/Details/LiveGameDetails/Doppelkopf/NewDokoRoundWidget/recolumn.h \
    Gui/Details/LiveGameDetails/Doppelkopf/NewDokoRoundWidget/hochzeitcolumn.h \
    Server/servicedescription.h \
    Server/soapStub.h \
    Server/soapprojectstatsService.h \
    Server/soapprojectstatsProxy.h \
    Server/soapH.h \
    Server/projectstats.nsmap \
    Server/stdsoap2.h \
    Server/server.h \
    Server/stdsoap2.h \
    Gui/Misc/sheet.h \
    Database/Categories/smartfoldercategorie.h \
    Database/Filters/leaguerule.h

FORMS    += \
    Gui/Details/PlaceDetails/placedetailswidget.ui \
    Gui/Details/GameDetails/gamesummarywidget.ui \
    Gui/Details/GameDetails/gamedetailswidget.ui \
    Gui/Details/DrinkDetails/DrinkDetailsWidget.ui \
    Gui/Filter/newleaguedialog.ui \
    Gui/Misc/newrowwidget.ui \
    Gui/Wizards/NewGame/wizardsidewidget.ui \
    Gui/Wizards/NewGame/skatlivegameoptionswidget.ui \
    Gui/Wizards/NewGame/offlinesummarywidget.ui \
    Gui/Wizards/NewGame/offlinegameresultwidget.ui \
    Gui/Wizards/NewGame/offlinegameoptionswidget.ui \
    Gui/Wizards/NewGame/offlinedetailledgamedokowidget.ui \
    Gui/Wizards/NewGame/livesummarywidget.ui \
    Gui/Wizards/NewGame/liveofflinegamewidget.ui \
    Gui/Wizards/NewGame/livegamegeneraloptionswidget.ui \
    Gui/Wizards/NewGame/livedokogameoptionswidget.ui \
    Gui/Wizards/NewGame/dokolivegamegroupbox.ui \
    Gui/Details/LiveGameDetails/livegamesettingswidget.ui \
    Gui/Details/LiveGameDetails/endlivegamewidget.ui \
    Gui/Details/LiveGameDetails/Doppelkopf/schmeissereiwidget.ui \
    Gui/Details/LiveGameDetails/Doppelkopf/newdokoroundwidget.ui \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamerowwindow.ui \
    Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamedetailswidget.ui \
    Gui/Details/LiveGameDetails/choosedrinkcountdialog.ui \
    Gui/Details/LiveGameDetails/beerplayerwidget.ui \
    Gui/Details/LiveGameDetails/adddrinkwidget.ui \
    Gui/Details/PlayerDetails/playerdetailswidget.ui \
    Gui/Details/PlayerDetails/playerstatswidget.ui \
    Gui/Details/PlayerDetails/abstractplayerstatswidget.ui \
    Gui/Details/PlayerDetails/dokoplayerstatswidget.ui

OTHER_FILES += \
    Server/ps.xsd \
    Server/projectstats.wsdl \
    Server/projectstats.playerById.res.xml \
    Server/projectstats.playerById.req.xml \
    Server/ps.xsd \
    Server/projectstats.wsdl \
    Server/projectstats.playerList.res.xml \
    Server/projectstats.playerList.req.xml \
    Server/projectstats.playerById.res.xml \
    Server/projectstats.playerById.req.xml

RESOURCES += Ressources/Ressources.qrc \
    Ressources/drinks.qrc




#
# Platform dependend stuff
#

macx {
    HEADERS += Misc/cocoainitializer.h \
                 Misc/Updater/sparkleupdater.h
    OBJECTIVE_SOURCES += Misc/cocoainitializer.mm \
                        Gui/Misc/macwindowcontroller.mm \
                        Misc/Updater/sparkleupdater.mm

    LIBS += -F$$PWD/../frameworks/ \
            -framework AppKit \
            -framework Sparkle \
            -L$$PWD/../lib/LBDatabase/lib/ -llbdatabase

    INCLUDEPATH += $$PWD/../lib/LBDatabase/include \
                    $$PWD/../frameworks/Sparkle.framework/Headers

    PRE_TARGETDEPS += $$PWD/../lib/LBDatabase/lib/liblbdatabase.a

    PRIVATE_FRAMEWORKS.files = $$PWD/../frameworks/Sparkle.framework
    PRIVATE_FRAMEWORKS.path = Contents/Frameworks
    QMAKE_BUNDLE_DATA += PRIVATE_FRAMEWORKS
}

win32 {
    LIBS += -lws2_32 \
            -L$$PWD/frameworks/WinSparkle-0.3 \
            -lWinSparkle

    CONFIG(release, debug|release): {
        PRE_TARGETDEPS += $$OUT_PWD/../lib/LBDatabase/src/release/lbdatabase.lib
        LIBS += -L$$OUT_PWD/../lib/LBDatabase/src/release/ -llbdatabase
    }
    else:CONFIG(debug, debug|release):  {
        PRE_TARGETDEPS += $$OUT_PWD/../lib/LBDatabase/src/debug/lbdatabase.lib
        LIBS += -L$$OUT_PWD/../lib/LBDatabase/src/debug/ -llbdatabase
    }

    SOURCES += Misc/Updater/winsparkleupdater.cpp
    HEADERS += Misc/Updater/winsparkleupdater.h
}
