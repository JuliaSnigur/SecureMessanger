

CONFIG += c++11

PRECOMPILED_HEADER = stable.h
CONFIG -= precompile_header

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE += app


# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
#

DISTFILES += \
    root.pri\
    common.pri\
    app.pri\
    lib.pri


##################################

TEMPLATE = subdirs

SUBDIRS += \
    src/ServerLib\
    src/Server\
    src/SSLServerLib\
    src/SSLClientLib\
    src/ClientLib\
    src/GuiLib\
    src/Client \
    src/DBLib \
    src/ParseDataLib


Client.depends = ClientLib
Client.depends=GuiLib
Client.depends=DBLib

Server.depends = ServerLib

ClientLib.depends=ParseDataLib
ServerLib.depends=ParseDataLib
Client.depends=ParseDataLib


##################################
