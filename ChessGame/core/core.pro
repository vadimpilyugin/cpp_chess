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

SOURCES += \
    chessgame.cpp \
    chessrules.cpp

HEADERS += \
    chessgame.h \
    chessrules.h \
    dark.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
