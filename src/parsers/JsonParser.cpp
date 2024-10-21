

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QResource>
#include "JsonParser.hpp"

void JsonParser::parseFile(const QString& path)
{

}

QSet<QString>* JsonParser::parseAutocompleteJsonArray(const QString& path)
{
    try
    {
        QResource res(path);
        if (!res.isValid())
        {
            qDebug() << "Resource is not valid";
            return {};
        }

        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Could not open file";
            return {};
        }
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if(!doc.isObject())
        {
            //TODO: handle error
            file.close();
            qDebug() << "Json has incorrect format";
            return {};
        }
        QJsonObject obj = doc.object();
        if (!obj.contains("keywords") || !obj["keywords"].isArray())
        {
            //TODO: handle error
            qDebug() << "Json has incorrect format: no keywords array";
            file.close();
            return {};
        }

        QJsonArray keywordsArray = obj["keywords"].toArray();

        auto* keywordSet = new QSet<QString>();
        for (const auto& keyword : obj["keywords"].toArray())
        {
            keywordSet->insert(keyword.toString());
        }
        return keywordSet;
    }
    catch (QJsonParseError& e)
    {
        qDebug() << e.errorString();
    }
    catch (std::exception& e)
    {
        qDebug() << e.what();
    }
    catch (...)
    {
        qDebug() << "An error occured";
    }
    return {};
}
