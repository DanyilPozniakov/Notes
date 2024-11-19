#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickTextDocument>
#include <QDebug>
#include <iostream>
#include "src/TextEditor/TextHandler.h"
#include "src/CoreApp/AppCore.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Notes/qml/main.qml"));
    TextHandler textHandler;
    AppCore coreApplication;
    engine.rootContext()->setContextProperty("textHandler",&textHandler);
    engine.rootContext()->setContextProperty("application",&coreApplication);
    engine.load(url);

    QObject* qmlRootObject = engine.rootObjects().first();
    if(qmlRootObject)
    {
        QObject* textEditObject = qmlRootObject->findChild<QObject*>("textEditor", Qt::FindChildrenRecursively);
        textHandler.setTextDocument(textEditObject);
    }

    return app.exec();
}


