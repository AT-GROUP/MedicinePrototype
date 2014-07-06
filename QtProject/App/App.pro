QT       += sql core

TARGET = App
TEMPLATE = app

SOURCES += ../../src/App/main.C

LIBS += -L$$OUT_PWD/../Database/ -lDatabase

INCLUDEPATH += $$PWD/../Database
DEPENDPATH += $$PWD/../Database

QMAKE_CXXFLAGS += -std=c++0x
