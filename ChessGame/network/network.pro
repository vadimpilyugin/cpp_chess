#-------------------------------------------------
#
# Project created by QtCreator 2017-06-23T20:56:48
#
#-------------------------------------------------

QT       -= core gui

TARGET = network
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../common

SOURCES += network.cpp \
    chess_connector.cpp

HEADERS += network.h \
    zmq.h \
    zmq.hpp \
    chess_connector.h \
    real_chess_connector.h
