#-------------------------------------------------
#
# Project created by QtCreator 2015-03-08T22:31:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cubepass
TEMPLATE = app

SOURCES += main.cpp\
        loginscreen.cpp \
    createuser.cpp \
    mainwindow.cpp \
    newitem.cpp

HEADERS  += loginscreen.h \
    stdafx.h \
    createuser.h \
    mainwindow.h \
    newitem.h

FORMS    += loginscreen.ui \
    createuser.ui \
    mainwindow.ui \
    newitem.ui


unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/bin/cube-lib/ -lcube-lib

INCLUDEPATH += $$PWD/../../../../../usr/local/include/cube-lib
DEPENDPATH += $$PWD/../../../../../usr/local/include/cube-lib
