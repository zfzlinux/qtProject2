#-------------------------------------------------
#
# Project created by QtCreator 2017-12-13T14:59:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tcpsocketDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpsocket.cpp

HEADERS  += mainwindow.h \
    tcpsocket.h

FORMS    += mainwindow.ui
