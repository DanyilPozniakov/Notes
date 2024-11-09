
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


QStringList JsonParser::parseJsonArray(const QString &path)
{
    try
    {
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Could not open file";
            return {};
        }

        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
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
    return QStringList();
}
