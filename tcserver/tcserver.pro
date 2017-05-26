#-------------------------------------------------
#
# Project created by QtCreator 2017-05-20T16:11:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tcserver
TEMPLATE = app

INCLUDEPATH +=  netserver/inc \
				timecode_server \
				cristian_server \
				processor \


SOURCES += main.cpp\
        mainwindow.cpp \
    tcsyncserverthread.cpp \
    timecode_server/timecode_server.cpp \
    netserver/src/server_factory.cpp \
    netserver/src/fdlooper.cpp \
    netserver/src/process_manager.cpp \
    netserver/src/tcplistener.cpp \
    netserver/src/ipaddr.cpp \
    netserver/src/fdlistenconnection.cpp \
    netserver/src/tinaserver.cpp \
    netserver/src/fdlistener.cpp \
    netserver/src/observer.cpp \
    netserver/src/observable.cpp \
    netserver/src/fdclient.cpp \
    netserver/src/fdconnection.cpp \
    netserver/src/tcpclient.cpp \
    netserver/src/request.cpp \
    netserver/src/sender.cpp \
    netserver/src/utility.cpp \
    timecode_server/test_timecode_processor.cpp \
    cristian_server/cristian_server.cpp \
    cristian_server/test_cristian_processor.cpp \
    netserver/src/udplistener.cpp \
    cristianserverthread.cpp \
    netserver/src/udpclient.cpp \
    netserver/src/runner.cpp \
    netserver/src/pthread_runner.cpp \
    netserver/src/server.cpp \
    processor/cristian_processor.cpp \
    processor/dummy_service.cpp \
    processor/parse.cpp \
    processor/response.cpp \
    processor/service_handler_get_tc.cpp \
    processor/service_handler_sync_tc.cpp \
    processor/tc_processor.cpp

HEADERS  += mainwindow.h \
    netserver/inc/fdlooper.h \
    netserver/inc/observable.h \
    netserver/inc/observer.h \
    netserver/inc/processor.h \
    netserver/inc/processor_manager.h \
    netserver/inc/runner.h \
    netserver/inc/server_factory.h \
    netserver/inc/tcplistener.h \
    netserver/inc/utility.h \
    netserver/inc/fdconnection.h \
    netserver/inc/ipaddr.h \
    netserver/inc/fdlistenconnection.h \
    netserver/inc/tinaserver.h \
    timecode_server/timecode_server.h \
    netserver/inc/fdlistener.h \
    netserver/inc/fdclient.h \
    netserver/inc/tcpclient.h \
    netserver/inc/request.h \
    netserver/inc/sender.h \
    processor/common_data.h \
    processor/cristian_processor_impl.h \
    processor/service_handler_base.h \
    processor/service_handler_get_tc_impl.h \
    processor/service_handler_set_tc_impl.h \
    processor/service_handler_sync_tc_impl.h \
    processor/tc_processor_impl.h \
    timecode_server/test_timecode_processor.h \
    cristian_server/cristian_server.h \
    cristian_server/test_cristian_processor.h \
    netserver/inc/udplistener.h \
    cristianserverthread.h \
    tcsyncserverthread.h \
    netserver/inc/udpclient.h \
    netserver/inc/pthread_runner.h \
    netserver/inc/server.h \
    processor/cristian_processor.h \
    processor/dummy_service.h \
    processor/parse.h \
    processor/response.h \
    processor/service.h \
    processor/service_handler.h \
    processor/service_handler_get_tc.h \
    processor/service_handler_sync_tc.h \
    processor/tc_processor.h


FORMS    += mainwindow.ui
