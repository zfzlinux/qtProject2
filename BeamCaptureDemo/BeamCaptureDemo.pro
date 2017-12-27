#-------------------------------------------------
#
# Project created by QtCreator 2017-12-26T13:50:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BeamCaptureDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    capturethread.cpp \
    sendcmd.cpp

HEADERS  += mainwindow.h \
    capturethread.h \
    cmdconfig.h \
    sendcmd.h \
    configure/dopplerdatafileconfigure.h \
    configure/gheader.h \
    configure/instrument.h

FORMS    += mainwindow.ui
