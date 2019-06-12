#-------------------------------------------------
#
# Project created by QtCreator 2019-04-13T15:10:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sokoban
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    Game.cpp \
    MainWindow.cpp \
    Map/Map.cpp \
    Map/MapList.cpp \
    Map/MapManager.cpp \
    Map/TextMap.cpp \
    MapItems/BoxMapItem.cpp \
    MapItems/FloorMapItem.cpp \
    MapItems/MapItemBase.cpp \
    MapItems/NoneMapItem.cpp \
    MapItems/PlayerMapItem.cpp \
    MapItems/StockMapItem.cpp \
    SpriteManager.cpp \
    main.cpp \
    Map\MapWidget.cpp \
    MapItems\WallMapItem.cpp \
    MapItems\NulledMapItem.cpp

HEADERS += \
    Array2D.h \
    Error.h \
    Game.h \
    MainWindow.h \
    Map/Map.h \
    Map/MapList.h \
    Map/MapManager.h \
    Map/TextMap.h \
    MapItems/BoxMapItem.h \
    MapItems/FloorMapItem.h \
    MapItems/NoneMapItem.h \
    MapItems/NulledMapItem.h \
    MapItems/PlayerMapItem.h \
    MapItems/StockMapItem.h \
    Map\MapSaver.h \
    Map\MapWidget.h \
    MapItems\MapItemType.h \
    MapItems\WallMapItem.h \
    MapItems\MapItemBase.h \
    MapItems\NulledMapItem.h \
    Singleton.h \
    SpriteManager.h

FORMS += \
	MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Doc/sbmap_structure.ru.txt \
    Doc/Sprites_and_Tiles_info.txt

#
# For RU-console
#
QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251
