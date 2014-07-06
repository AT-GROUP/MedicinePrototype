QT       += core sql

TEMPLATE = lib

CONFIG   += console qt
CONFIG   -= app_bundle

SOURCES += \
   ../../src/Database/Database.C

HEADERS += \
    ../../src/Database/Database.H

QMAKE_CXXFLAGS += -std=c++0x
