#include <QFile>
#include <QDir>


#include "FileHandler.h"


FileHandler::FileHandler(QObject* parent)
{
    QDir dir;
    if(dir.mkdir("Files")) qDebug() << "Directory Files created";

    m_pathToFiles = dir.absolutePath() + "/Files/";

}

void FileHandler::createFile(const QString& fileName, const QString& path)
{
    QDir dir;
    QString filePath = m_pathToFiles + fileName + ".txt"; //TODO: add .h .cpp .qml logic
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly))
    {
        qDebug() << "File created";
        file.close();
    }
    else
    {
        qDebug() << "File not created";
    }
}

void FileHandler::updateFile(const QString& fileName, const QString& text)
{
}
