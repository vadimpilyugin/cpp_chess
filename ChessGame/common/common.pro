#-------------------------------------------------
#
# Project created by QtCreator 2017-06-23T20:59:10
#
#-------------------------------------------------

QT       -= core gui

TARGET = common
TEMPLATE = lib
CONFIG += staticlib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    achessgame.h \
    adarkchessgame.h \
    chesscolor.h \
    command.h \
    ichessobserver.h \
    my_exception.h \
    piece.h \
    player.h \
    printer.h \
    serialize.h \
    tile.h

SOURCES += \
    achessgame.cpp \
    adarkchessgame.cpp \
    chesscolor.cpp \
    command.cpp \
    piece.cpp \
    serialize.cpp
