include( ../../common.pri )

DESTDIR = $${LIBS_PATH}/
win32: DLLDESTDIR = $${BIN_PATH}/
QMAKE_TARGET_COPYRIGHT = (c) My Company Name

QT+=qml sql

TARGET = GuiLib$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    guiqml.cpp \
    FriendElement.cpp \
    dialogelement.cpp

HEADERS += \
    guiqml.h \
    FriendElement.h \
    dialogelement.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += $${PARSEDATALIB_LIBRARY}
INCLUDEPATH += $${PARSEDATALIB_INCLUDEPATH}

GuiLib.depends = ParseDataLib

DISTFILES += \
    functions.js \
    Authorization.qml \
    main.qml \
    Registration.qml \
    MainWindow.qml \
    MyRow.qml \
    Connection.qml

