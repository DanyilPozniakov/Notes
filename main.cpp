#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/texthandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Notes/main.qml"));
    TextHandler textHandler;
    engine.rootContext()->setContextProperty("textHandler",&textHandler);
    engine.load(url);

    return app.exec();



}
