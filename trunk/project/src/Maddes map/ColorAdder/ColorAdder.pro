#-------------------------------------------------
#
# Project created by QtCreator 2012-04-20T14:20:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ColorAdder
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/release/ -lopencv_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/debug/ -lopencv_core
else:symbian: LIBS += -lopencv_core
else:unix: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lopencv_core

INCLUDEPATH += $$PWD/../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../usr/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/release/ -lopencv_highgui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/debug/ -lopencv_highgui
else:symbian: LIBS += -lopencv_highgui
else:unix: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lopencv_highgui

INCLUDEPATH += $$PWD/../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../usr/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/release/ -lopencv_gpu
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/debug/ -lopencv_gpu
else:symbian: LIBS += -lopencv_gpu
else:unix: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lopencv_gpu

INCLUDEPATH += $$PWD/../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../usr/include




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../../usr/lib/release/ -lopencv_imgproc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../../usr/lib/debug/ -lopencv_imgproc
else:symbian: LIBS += -lopencv_imgproc
else:unix: LIBS += -L$$PWD/../../../../../../../../usr/lib/ -lopencv_imgproc

INCLUDEPATH += $$PWD/../../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../../usr/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../../usr/lib/release/ -lopencv_flann
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../../usr/lib/debug/ -lopencv_flann
else:symbian: LIBS += -lopencv_flann
else:unix: LIBS += -L$$PWD/../../../../../../../../usr/lib/ -lopencv_flann

INCLUDEPATH += $$PWD/../../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../../usr/include
