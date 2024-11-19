//
// Created by pozni on 12.11.2024.
//

#include "AppCore.h"

AppCore::AppCore(QObject* parent)
{
    fileHandler = new FileHandler();
    assert(fileHandler && "In CoreApplication constructor fileHandler is null");
}

void AppCore::createNewFile(const QString& fileName)
{
    fileHandler->createFile(fileName);
}
