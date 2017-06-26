#-------------------------------------------------
#
# Project created by QtCreator 2017-06-24T10:35:53
#
#-------------------------------------------------

QT       -= core gui

TARGET = core
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH+=../common
INCLUDEPATH+=../network

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    chessgame.h \
    dark.h \
    darkchessgame.h \
    darkchessrules.h \
    networkdarkchessgame.h

SOURCES += \
    chessgame.cpp \
    darkchessgame.cpp \
    darkchessrules.cpp \
    networkdarkchessgame.cpp
