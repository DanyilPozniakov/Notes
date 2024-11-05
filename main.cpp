#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickTextDocument>
#include <QQuickTextDocument>
#include <QDebug>
#include <iostream>
#include "src/texthandler.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Notes/main.qml"));
    TextHandler textHandler;
    engine.rootContext()->setContextProperty("textHandler",&textHandler);
    engine.load(url);

    QObject* qmlRootObject = engine.rootObjects().first();
    if(qmlRootObject)
    {
        QObject* textEditObject = qmlRootObject->findChild<QObject*>("textEditor", Qt::FindChildrenRecursively);
        textHandler.setTextDocument(textEditObject);
    }

    return app.exec();

}


