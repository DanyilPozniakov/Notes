#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <TextHandler.h>
#include <QQmlEngine>
#include <QQmlComponent>

#include "src/CoreApp/AppCore.h"
#include "src/CoreApp/Models/CategoryModel.h"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    TextHandler textHandler;
    AppCore coreApplication;
    engine.rootContext()->setContextProperty("textHandler",&textHandler);
    engine.rootContext()->setContextProperty("application",&coreApplication);

    qmlRegisterType<CategoryModel>("CategoryModel",1,0,"CategoryModel");

    const QUrl url(QStringLiteral("qrc:/Notes/qml/main.qml"));
    engine.load(url);

    QObject* qmlRootObject = engine.rootObjects().first();
    if(qmlRootObject)
    {
        auto* textEditObject = qmlRootObject->findChild<QObject*>("textEditor", Qt::FindChildrenRecursively);
        textHandler.setTextDocument(textEditObject);
    }

    return app.exec();
}


