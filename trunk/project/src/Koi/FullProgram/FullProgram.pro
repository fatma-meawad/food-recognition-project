#-------------------------------------------------
#
# Project created by QtCreator 2012-04-26T20:30:28
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = FullProgram
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    data.cpp \
    videocapture.cpp \
    breathing.cpp \
    blinking.cpp \
    featuredetection.cpp \
    fuzzymodel.cpp \
    pulse.cpp \
    preprocessing.cpp \
    painting.cpp \
    facefeatures.cpp



unix:!macx:!symbian: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect

INCLUDEPATH += $$PWD/../../../../../../../usr/include/opencv-2.3.1
DEPENDPATH += $$PWD/../../../../../../../usr/include/opencv-2.3.1

INCLUDEPATH += $$PWD/../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../usr/include

HEADERS += \
    data.h \
    Includes.h \
    videocapture.h \
    breathing.h \
    blinking.h \
    featuredetection.h \
    fuzzymodel.h \
    pulse.h \
    preprocessing.h \
    painting.h \
    facefeatures.h


