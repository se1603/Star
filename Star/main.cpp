#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "client.h"
#include "audience.h"
#include "collection.h"
#include "record.h"
#include "videoplayer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Client>("Star", 1, 0, "Client");
    qmlRegisterType<VideoPlayer>("Star", 1, 0, "VideoPlayer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
