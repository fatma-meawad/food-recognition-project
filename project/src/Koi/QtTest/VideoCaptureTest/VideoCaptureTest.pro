#-------------------------------------------------
#
# Project created by QtCreator 2012-04-21T18:01:05
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = VideoCaptureTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp


unix:!macx:!symbian: LIBS += -L$$PWD/../../../../usr/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include
