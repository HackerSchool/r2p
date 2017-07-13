#-------------------------------------------------
#
# Project created by QtCreator 2017-03-25T18:14:26
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
        client.cpp \
        connectWindow.cpp

HEADERS  += client.h \
		connectWindow.h

FORMS    += client.ui \
			connectWindow.ui

RESOURCES += icons.qrc

QTPLUGIN += qsvg

CONFIG -= debug
CONFIG += release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../r2p/release/ -lr2p
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../r2p/debug/ -lr2p
else:unix: LIBS += -L$$PWD/../r2p/ -lr2p

INCLUDEPATH += $$PWD/../r2p
DEPENDPATH += $$PWD/../r2p

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../r2p/release/libr2p.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../r2p/debug/libr2p.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../r2p/release/r2p.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../r2p/debug/r2p.lib
else:unix: PRE_TARGETDEPS += $$PWD/../r2p/libr2p.a
