#-------------------------------------------------
#
# Project created by QtCreator 2012-04-26T15:30:32
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = AreYouTired
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    data.cpp \
    features.cpp \
    videocapture.cpp \
    pulse.cpp \
    breathing.cpp \
    blinking.cpp \
    preprocessing.cpp \
    painting.cpp \
    featuredetecition.cpp \
    fuzzymodel.cpp

HEADERS += \
    data.h \
    features.h \
    videocapture.h \
    pulse.h \
    breathing.h \
    blinking.h \
    preprocessing.h \
    painting.h \
    featuredetecition.h \
    fuzzymodel.h \
    Includes.h

unix:!macx:!symbian: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lopencv_highgui -lopencv_core -lopencv_imgproc -lopencv_objdetect

