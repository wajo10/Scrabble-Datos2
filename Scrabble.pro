#-------------------------------------------------
#
# Project created by QtCreator 2019-03-16T16:33:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scrabble
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    palabra.cpp \
    jugador.cpp \
    tablero.cpp \
    sala.cpp \
    bolsa.cpp \
    ficha.cpp \
    linkedlist.cpp \
    node.cpp \
    tablero_servidor.cpp \
    tablero_cliente.cpp \
    pantalla.cpp \
    botones.cpp \
    traductorcliente.cpp \
    traductorservidor.cpp \
    socket.cpp \
    comodin.cpp

HEADERS += \
        mainwindow.h \
    palabra.h \
    jugador.h \
    tablero.h \
    sala.h \
    bolsa.h \
    ficha.h \
    linkedlist.h \
    node.h \
    tablero_servidor.h \
    tablero_cliente.h \
    pantalla.h \
    botones.h \
    traductorcliente.h \
    traductorservidor.h \
    socket.h \
    comodin.h

FORMS += \
        mainwindow.ui \
    comodin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource.qrc
