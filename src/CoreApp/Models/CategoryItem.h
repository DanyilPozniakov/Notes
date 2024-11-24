#ifndef CATEGORY_H
#define CATEGORY_H

#include <QList>
#include <QString>
#include "File.h"

class CategoryItem {
public:
    CategoryItem(QString name) : name(name) {}

    QString name;
    QList<File> files = {File("file1"), File("file2")};
};

Q_DECLARE_METATYPE(CategoryItem)

#endif //CATEGORY_H
