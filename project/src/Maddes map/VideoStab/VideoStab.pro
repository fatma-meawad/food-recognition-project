#-------------------------------------------------
#
# Project created by QtCreator 2012-04-24T23:23:42
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = VideoStab
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    videocapture.cpp \
    head.cpp

HEADERS += \
    videocapture.h \
    Includes.h \
    head.h

unix:!macx:!symbian: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lopencv_highgui -lopencv_core -lopencv_imgproc -lopencv_objdetect




INCLUDEPATH += $$PWD/../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../usr/include
