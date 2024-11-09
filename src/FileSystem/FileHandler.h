#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>

class FileHandler : public QObject
{
    Q_OBJECT

public:
    void openFile(const QString& path);
    void saveFile(const QString& path, const QObject* file);
};

#endif // FILEHANDLER_H


