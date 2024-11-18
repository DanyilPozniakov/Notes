#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H
#include <QObject>

#include "src/FileSystem/FileHandler.h"

class CoreApplication : public QObject
{
    Q_OBJECT

public:
    CoreApplication(QObject *parent = nullptr);

public slots:
    void createNewFile(const QString& fileName);


private:
    FileHandler* fileHandler;

};



#endif //COREAPPLICATION_H
