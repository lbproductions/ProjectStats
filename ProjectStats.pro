TEMPLATE = subdirs

SUBDIRS = lib/LBDatabase/src/LBDatabase.pro \
            src/ProjectStats.pro

CONFIG += ordered

DEFINES *= QT_USE_QSTRINGBUILDER # makes string concatenation faster

#This makes `make Documentation` possible
Documentation.target = Documentation
Documentation.commands = $$PWD/util/doxygen-1.7.5.1/doxygen $$PWD/util/documentation/QtDoxygen/DoxyFile.debug
Documentation.depends = FORCE
QMAKE_EXTRA_TARGETS += Documentation
