#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>

class FileHandler : public QObject
{
    Q_OBJECT


public:
    FileHandler(QObject* parent = nullptr);

    void createFile (const QString& fileName, const QString& path = {});
    void updateFile(const QString& fileName, const QString& text);

private:
    QString m_pathToFiles;



};

#endif // FILEHANDLER_H


