#-------------------------------------------------
#
# Project created by QtCreator 2014-05-17T16:22:39
#
#-------------------------------------------------

QT       += core gui

CONFIG += link_pkgconfig c++11
PKGCONFIG += libmissilelauncher

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Missile-Launcher
TEMPLATE = app


SOURCES += main.cpp\
        launchwindow.cpp

HEADERS  += launchwindow.h

FORMS    += launchwindow.ui
