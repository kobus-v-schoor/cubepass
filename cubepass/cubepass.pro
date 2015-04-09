#-------------------------------------------------
#
# Project created by QtCreator 2015-03-08T22:31:46
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cubepass
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    loginscreen.cpp \
    createuser.cpp \
    mainwindow.cpp \
    newitem.cpp \
    itemdetails.cpp \
    categorymanager.cpp \
    deleteaccount.cpp \
    restoreaccount.cpp \
    backupaccount.cpp \
    restoreuserexists.cpp \
    changepword.cpp \
    aboutscreen.cpp \
    helpscreen.cpp \
    generatepword.cpp

HEADERS  += loginscreen.h \
    stdafx.h \
    createuser.h \
    mainwindow.h \
    newitem.h \
    itemdetails.h \
    categorymanager.h \
    deleteaccount.h \
    restoreaccount.h \
    backupaccount.h \
    restoreuserexists.h \
    changepword.h \
    aboutscreen.h \
    helpscreen.h \
    generatepword.h

FORMS += loginscreen.ui \
    createuser.ui \
    mainwindow.ui \
    newitem.ui \
    itemdetails.ui \
    categorymanager.ui \
    deleteaccount.ui \
    restoreaccount.ui \
    backupaccount.ui \
    restoreuserexists.ui \
    changepword.ui \
    aboutscreen.ui \
    helpscreen.ui \
    generatepword.ui

RESOURCES += ImageResources.qrc
win32 : RC_FILE = "./rsc/WindowExecIcon.rc"

SOURCES += "$(CUBE-LIB)/include/cube-lib-src.cpp"
INCLUDEPATH += "$(CUBE-LIB)/include"
