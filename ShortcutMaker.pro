#-------------------------------------------------
#
# Project created by QtCreator 2016-11-09T19:39:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShortcutMaker
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -pedantic


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
