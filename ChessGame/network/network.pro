#-------------------------------------------------
#
# Project created by QtCreator 2017-06-23T20:56:48
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11

TARGET = network
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../common

SOURCES += network.cpp \
    chessconnector.cpp

HEADERS += network.h \
    zmq.h \
    zmq.hpp \
    realchessconnector.h
