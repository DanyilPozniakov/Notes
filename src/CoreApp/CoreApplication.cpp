//
// Created by pozni on 12.11.2024.
//

#include "CoreApplication.h"

CoreApplication::CoreApplication(QObject* parent)
{
    fileHandler = new FileHandler();
    assert(fileHandler && "In CoreApplication constructor fileHandler is null");
}

void CoreApplication::createNewFile(const QString& fileName)
{
    fileHandler->createFile(fileName);
}
