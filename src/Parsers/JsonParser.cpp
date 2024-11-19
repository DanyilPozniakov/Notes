#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QResource>
#include "JsonParser.h"


QStringList JsonParser::parseKeywords()
{
    try
    {
        QFile file(":/keywords.json");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Could not open file";
            return {};
        }

        QByteArray data = file.readAll();
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
        if(parseError.error != QJsonParseError::NoError)
        {
            qWarning() << parseError.errorString();
            return {};
        }

        QJsonObject obj = doc.object();
        QJsonArray array = obj["keywords"].toArray();
        QStringList list;
        for (const auto& keyword : array)
        {
            list.append(keyword.toString());
        }
        return list;
    }

    catch (QJsonParseError& e)
    {
        qWarning() << e.errorString();
    }
    catch (std::exception& e)
    {
        qWarning() << e.what();
    }
    catch (...)
    {
        qWarning() << "Unknown exception in JsonParser::parseKeywords";
    }
    return {};
}


