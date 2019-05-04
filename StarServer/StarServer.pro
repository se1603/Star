TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    server.cpp \
    threadpool.cpp \
    network.cpp \
    relationalbroker.cpp \
    movieandtelevisionbroker.cpp \
    audiencebroker.cpp \
    audience.cpp \
    collection.cpp \
    record.cpp

HEADERS += \
    server.h \
    threadpool.h \
    network.h \
    relationalbroker.h \
    movieandtelevisionbroker.h \
    audiencebroker.h \
    audience.h \
    collection.h \
    record.h

LIBS += -lboost_system -lpthread -lboost_thread -ljsoncpp -lmysqlclient
