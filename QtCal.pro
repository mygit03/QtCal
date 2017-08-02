#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T16:26:36
#
#-------------------------------------------------

QT       += core gui
#Qt       += webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCal
TEMPLATE = app

RC_FILE = myapp.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    aboutcalculate.cpp \
#    browser.cpp \
    help.cpp \
    matrixcal.cpp \
    equcal.cpp \
    painter/painter.cpp \
    painter/painterwidget.cpp \
    painter/palette.cpp \
    painter/penstyledelegate.cpp \
    painter/previewlabel.cpp \
    draw.cpp \
    funcdraw.cpp \
    plotter.cpp

HEADERS  += mainwindow.h \
    aboutcalculate.h \
#    browser.h \
    help.h \
    matrixcal.h \
    equcal.h \
    painter/painter.h \
    painter/painterwidget.h \
    painter/palette.h \
    painter/penstyledelegate.h \
    painter/previewlabel.h \
    draw.h \
    funcdraw.h \
    plotter.h

FORMS    += mainwindow.ui \
    aboutcalculate.ui \
#    browser.ui \
    help.ui \
    matrixcal.ui \
    equcal.ui \
    draw.ui \
    funcdraw.ui \
    plotter.ui

RESOURCES += \
    painter/cal.qrc
