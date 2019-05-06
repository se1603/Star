#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "client.h"
#include "audience.h"
#include "collection.h"
#include "record.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

//    Client c;
//    c.connectServer();
    qmlRegisterType<Client>("Star",1,0,"Client");
    qmlRegisterType<Collection>("Star",1,0,"Collection");
    qmlRegisterType<Record>("Star",1,0,"Record");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
