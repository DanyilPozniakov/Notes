#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H
#include <QObject>

#include "src/FileSystem/FileHandler.h"

class AppCore : public QObject
{
    Q_OBJECT

public:
    AppCore(QObject *parent = nullptr);

public slots:
    void createNewFile(const QString& fileName);


private:
    FileHandler* fileHandler;

};

#endif //COREAPPLICATION_H
