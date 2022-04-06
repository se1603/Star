TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        datasource.cpp \
        main.cpp \
        rtpsession.cpp \
        rtsprtpdefine.cpp \
        rtspserver.cpp \
        rtspsession.cpp \
        socket.cpp \
        tcpsocket.cpp \
        threadpool.cpp \
        tsfilereader.cpp \
        tsparse.cpp

HEADERS += \
    datasource.h \
    rtpsession.h \
    rtsprtpdefine.h \
    rtspserver.h \
    rtspsession.h \
    socket.h \
    tcpsocket.h \
    threadpool.h \
    tsfilereader.h \
    tsparse.h

LIBS += -lpthread
