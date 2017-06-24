#-------------------------------------------------
#
# Project created by QtCreator 2017-06-23T23:41:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app

INCLUDEPATH+=../common
INCLUDEPATH+=../network

SOURCES += \
    aspectratiopixmaplabel.cpp \
    chessgameview.cpp \
    darkchessboardview.cpp \
    darkchessboardwidget.cpp \
    gameconnectionwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS  += \
    aspectratiopixmaplabel.h \
    chessgameview.h \
    darkchessboardview.h \
    darkchessboardwidget.h \
    gameconnectionwidget.h \
    ichessboardwidget.h \
    idarkchessboardwidget.h \
    mainwindow.h

FORMS += \
    chessgamewidget.ui \
    gameconnectionwidget.ui \
    mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../common/debug/ -lcommon
else:unix: LIBS += -L$$OUT_PWD/../common/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/release/libcommon.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/debug/libcommon.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/release/common.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/debug/common.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../common/libcommon.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../network/release/ -lnetwork
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../network/debug/ -lnetwork
else:unix: LIBS += -L$$OUT_PWD/../network/ -lnetwork

INCLUDEPATH += $$PWD/../network
DEPENDPATH += $$PWD/../network

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../network/release/libnetwork.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../network/debug/libnetwork.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../network/release/network.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../network/debug/network.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../network/libnetwork.a


win32 {
    ZEROMQPATH += "C:/Program Files (x86)/ZeroMQ 4.0.4"
    INCLUDEPATH+= $${ZEROMQPATH}"\include"
    LIBS += $${ZEROMQPATH}"/lib/libzmq-v120-mt-4_0_4.lib"
}
unix{
    INCLUDEPATH += $$PWD/../include
    LIBS += -L$$PWD/../lib -lzmq
}

RESOURCES += \
    images.qrc
