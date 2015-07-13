# ---------------------------------------------------------------------
# CubePass V3.0.0
#
# Author: Kobus van Schoor alias Cube777
# You are free to use, modify and distribute this software
# in any way you choose as long as you acknowledge the original author.
#
# You need to change the CUBE_DIR variable below (indicated by comment)
# to the dir that you installed cube-lib to if you modified the default
# install dir
# ---------------------------------------------------------------------


QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cubepass
TEMPLATE = app

CONFIG += c++11 debug_and_release

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

# ---------------------------------------------------------------------
# Change the value CUBE_DIR below to the install prefix you selected when running CMake.
# If you used the default CMake settings you do not need to change anything.
# Make sure your install path for cube-lib DOES NOT HAVE SPACES
# ---------------------------------------------------------------------

unix: CUBE_DIR = /usr/local/
win32 : CUBE_DIR = C:/cube-lib

unix: LIBS += -L$$CUBE_DIR/lib/cube-lib -lcube-encrypter -lcube-ini-parser -lcube-database

win32:CONFIG(release, debug|release): LIBS += -L$$CUBE_DIR/lib/ -llibcube-encrypter -llibcube-ini-parser -llibcube-database
else:win32:CONFIG(debug, debug|release): LIBS += -L$$CUBE_DIR/lib/ -llibcube-encrypterd -llibcube-ini-parserd -llibcube-databased

INCLUDEPATH += $$CUBE_DIR/include
DEPENDPATH += $$CUBE_DIR/include

unix {
TARGET.path = /usr/local/bin
TARGET.files = cubepass

desktop_file.path = /usr/share/applications
desktop_file.files = CubePass.desktop

icon.path = /usr/share/pixmaps
icon.files = rsc/cubepass.png

INSTALLS += desktop_file icon
}

win32 {
TARGET.path = '$(PROGRAMFILES)/CubePass'
TARGET.files = cubepass.exe
}

INSTALLS += TARGET
