#ifndef FILE_H
#define FILE_H

#include <QObject>
#include <QString>

class File {
    Q_GADGET
public:
    File() {};
    explicit File(QString name) : name(name) {};

    QString name;
    QString path;

    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QString path MEMBER path)
};

Q_DECLARE_METATYPE(File)


#endif //FILE_H
