QT += quick
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    audience.cpp \
    client.cpp \
    collection.cpp \
    film.cpp \
    movieandtelevision.cpp \
    network.cpp \
    record.cpp \
    region.cpp \
    variety.cpp \
    comic.cpp \
    videodecode.cpp \
    videoplayer.cpp

RESOURCES += \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


LIBS += -lboost_system -ljsoncpp -lavcodec -lavformat -lavdevice -lavfilter -lavutil -lswresample -lswscale -lpostproc \
        -lSDL2

HEADERS += \
    audience.h \
    client.h \
    collection.h \
    film.h \
    movieandtelevision.h \
    network.h \
    record.h \
    region.h \
    variety.h \
    comic.h \
    videodecode.h \
    videoplayer.h
