#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T16:02:50
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    image.cpp \
    colorbar.cpp

HEADERS  += mainwindow.h \
    image.h \
    colorbar.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
