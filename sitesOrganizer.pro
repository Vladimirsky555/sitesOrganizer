#-------------------------------------------------
#
# Project created by QtCreator 2018-07-07T15:45:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.4
QMAKE_TARGET_COMPANY = BearWin
QMAKE_TARGET_PRODUCT = sitesOrganizer
QMAKE_TARGET_DESCRIPTION = For organizing your sites
QMAKE_TARGET_COPYRIGHT = BearWin

win32: RC_ICONS = $$PWD/bin/images/app.ico

TARGET = CitesOrganizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    listitem.cpp \
    textitem.cpp \
    storage.cpp \
    listwidget.cpp \
    textwidget.cpp \
    categoryenter.cpp \
    nameenter.cpp \
    searchform.cpp \
    qregexphighlighter.cpp \
    movetocategory.cpp

HEADERS  += mainwindow.h \
    listitem.h \
    textitem.h \
    storage.h \
    listwidget.h \
    textwidget.h \
    categoryenter.h \
    nameenter.h \
    searchform.h \
    qregexphighlighter.h \
    movetocategory.h

FORMS    += mainwindow.ui \
    listwidget.ui \
    textwidget.ui \
    categoryenter.ui \
    nameenter.ui \
    searchform.ui \
    movetocategory.ui

RESOURCES += \
    bin/res.qrc
