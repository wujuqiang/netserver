#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T14:36:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tcclient
TEMPLATE = app

INCLUDEPATH +=  ../tcserver/netserver/inc \

SOURCES += main.cpp\
        mainwindow.cpp \
    ../tcserver/netserver/src/fdlistenconnection.cpp \
    ../tcserver/netserver/src/fdlistener.cpp \
    ../tcserver/netserver/src/fdlooper.cpp \
    ../tcserver/netserver/src/ipaddr.cpp \
    ../tcserver/netserver/src/observable.cpp \
    ../tcserver/netserver/src/observer.cpp \
    ../tcserver/netserver/src/process_manager.cpp \
    ../tcserver/netserver/src/server_factory.cpp \
    ../tcserver/netserver/src/tcplistener.cpp \
    ../tcserver/netserver/src/tinaserver.cpp \
    ../tcserver/netserver/src/fdconnection.cpp \
    ../tcserver/netserver/src/tcpclient.cpp \
    ../tcserver/netserver/src/fdclient.cpp \
    ../tcserver/netserver/src/request.cpp \
    ../tcserver/netserver/src/sender.cpp \
    ../tcserver/netserver/src/utility.cpp \
    ../tcserver/netserver/src/udplistener.cpp \
    ../tcserver/netserver/src/udpclient.cpp \
    ../tcserver/netserver/src/pthread_runner.cpp \
    ../tcserver/netserver/src/runner.cpp \
    ../tcserver/netserver/src/server.cpp

HEADERS  += mainwindow.h \
    ../tcserver/netserver/inc/fdconnection.h \
    ../tcserver/netserver/inc/fdlistenconnection.h \
    ../tcserver/netserver/inc/fdlistener.h \
    ../tcserver/netserver/inc/fdlooper.h \
    ../tcserver/netserver/inc/ipaddr.h \
    ../tcserver/netserver/inc/observable.h \
    ../tcserver/netserver/inc/observer.h \
    ../tcserver/netserver/inc/processor.h \
	../tcserver/netserver/inc/processor_manager.h \
    ../tcserver/netserver/inc/runner.h \
	../tcserver/netserver/inc/server_factory.h \
	../tcserver/netserver/inc/tcplistener.h \
    ../tcserver/netserver/inc/tinaserver.h \
	../tcserver/netserver/inc/utility.h \
    ../tcserver/netserver/inc/fdclient.h \
    ../tcserver/netserver/inc/request.h \
    ../tcserver/netserver/inc/sender.h \
    ../tcserver/netserver/inc/tcpclient.h \
    ../tcserver/netserver/inc/udplistener.h \
    ../tcserver/netserver/inc/udpclient.h \
    ../tcserver/netserver/inc/pthread_runner.h \
    ../tcserver/netserver/inc/server.h

FORMS    += mainwindow.ui
