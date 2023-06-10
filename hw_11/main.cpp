#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "organizer.h"
#include "mytablemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    qmlRegisterType<Organizer>("com.my.organizer",1,0,"Organizer");
    qRegisterMetaType<MyTableModel*>("MyTableModel*");
    engine.load(url);

    return app.exec();
}
