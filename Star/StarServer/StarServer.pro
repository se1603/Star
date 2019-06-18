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
    movieandtelevision.cpp \
    actor.cpp \
    director.cpp \
    film.cpp \
    controller.cpp \
    controllerfactory.cpp \
    browseandwatchcontroller.cpp \
    region.cpp \
    audience.cpp \
    audiencebroker.cpp \
    collection.cpp \
    record.cpp \
    audiencecontroller.cpp \
    variety.cpp \
    comic.cpp \
    drame.cpp \
    comment.cpp \
    commentbroker.cpp \
    commentcontroller.cpp

HEADERS += \
    server.h \
    threadpool.h \
    network.h \
    relationalbroker.h \
    movieandtelevisionbroker.h \
    movieandtelevision.h \
    actor.h \
    director.h \
    film.h \
    controller.h \
    controllerfactory.h \
    browseandwatchcontroller.h \
    region.h \
    audience.h \
    audiencebroker.h \
    collection.h \
    record.h \
    audiencecontroller.h \
    variety.h \
    comic.h \
    drame.h \
    comment.h \
    commentbroker.h \
    commentcontroller.h

LIBS += -lboost_system -lpthread -lboost_thread -ljsoncpp -lmysqlclient