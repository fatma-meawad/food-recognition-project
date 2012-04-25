#-------------------------------------------------
#
# Project created by QtCreator 2012-04-24T19:59:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = eyeDetection-proj
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

unix:!macx:!symbian: LIBS += -L$$PWD/../../../../usr/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include

unix:!macx:!symbian: LIBS += -L$$PWD/../../../../usr/local/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

HEADERS += \
    head.h
