include( ../../common.pri )
include( ../../lib.pri )

QT       += core gui widgets network



TARGET = ServerLib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += SERVERLIB_LIBRARY

HEADERS += $$files($${PWD}/*.h) \


SOURCES += $$files($${PWD}/*.cpp) \

PRECOMPILED_HEADER =stdafxs.h
CONFIG += precompile_header

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
    QMAKE_TARGET_PRODUCT = My Lib
    QMAKE_TARGET_DESCRIPTION = It is my library
}
