QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

CONFIG   += qt
CONFIG   -= app_bundle

LIBS += -L$$OUT_PWD/../Database/ -lDatabase

SOURCES += \
    ../../src/DatabaseWidget/databasewidget.C \

HEADERS += \
    ../../src/DatabaseWidget/databasewidget.H \

QMAKE_CXXFLAGS += -std=c++0x

FORMS += \
    ../../src/DatabaseWidget/databasewidget.ui \
