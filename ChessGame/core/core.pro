#-------------------------------------------------
#
# Project created by QtCreator 2017-06-24T10:35:53
#
#-------------------------------------------------

QT       -= gui
QT += core

QMAKE_CXXFLAGS += -std=c++11

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
    networkdarkchessgame.h

SOURCES += \
    networkdarkchessgame.cpp
