#-------------------------------------------------
#
# Project created by QtCreator 2013-11-30T11:56:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AesGui
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += \
    mainwindow.ui

LIBS += -L$$PWD/../AesLib/Release/ -lAesLib
INCLUDEPATH += $$PWD/../AesLib/AesLib
DEPENDPATH += $$PWD/../AesLib/AesLib
