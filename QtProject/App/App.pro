QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = App
TEMPLATE = app

SOURCES += ../../src/App/main.C \
    ../../src/App/mainwindow.C

LIBS += -L$$OUT_PWD/../Database/ -lDatabase
LIBS += -L$$OUT_PWD/../DatabaseWidget/ -lDatabaseWidget

INCLUDEPATH += $$PWD/../Database
DEPENDPATH += $$PWD/../Database

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    ../../src/App/mainwindow.H

FORMS += \
    ../../src/App/mainwindow.ui
