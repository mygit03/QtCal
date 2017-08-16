#-------------------------------------------------
#
# Project created by QtCreator 2017-08-16T09:29:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalculatorStatic
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutcalculate.cpp

HEADERS  += mainwindow.h \
    aboutcalculate.h

FORMS    += mainwindow.ui \
    aboutcalculate.ui

DISTFILES += \
    myapp.rc

RC_FILE  += \
    myapp.rc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lPlus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lPlusd

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/libPlus.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/libPlusd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/Plus.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/Plusd.lib

RESOURCES += \
    image.qrc
