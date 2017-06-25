#-------------------------------------------------
#
# Project created by QtCreator 2017-06-23T20:59:10
#
#-------------------------------------------------

QT       -= core gui

TARGET = common
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    chesscolor.cpp \
    command.cpp \
    piece.cpp \
    serialize.cpp \
    achessgame.cpp \
    adarkchessgame.cpp

HEADERS += \
    chesscolor.h \
    command.h \
    my_exception.h \
    piece.h \
    printer.h \
    serialize.h \
    tile.h \
    achessgame.h \
    adarkchessgame.h \
    ichessobserver.h \
    player.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
