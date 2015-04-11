# ---------------------------------------------------------------------
# CubePass V2.0.0
#
# Author: Kobus van Schoor alias Cube777
# You are free to use, modify and distribute this software
# in any way you choose as long as you acknowledge the original author.
#
# You need to set a environment variable in this projects settings
# name "CUBE-LIB" (without quotes) pointing to the root DIR of your
# cube-lib repository folder.
# ---------------------------------------------------------------------


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
