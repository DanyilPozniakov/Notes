#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H

#include <QAbstractListModel>
#include "CategoryItem.h"

class CategoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CategoryModel(QObject *parent = nullptr);

    enum Roles
    {
        CategoryName = Qt::UserRole + 1,
        FilesRole,
    };

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;


    Q_INVOKABLE void addCategory(const QString &categoryName);
    Q_INVOKABLE void removeItem(int index);
    Q_INVOKABLE void addNoteToCategory(int categoryIndex, const QString &noteName);
    Q_INVOKABLE void removeNoteFromCategory(int index, int noteIndex);

    int rowCount(const QModelIndex& parent) const override;

private:
    QList<CategoryItem> m_categories = {CategoryItem("STL"), CategoryItem("Algorithms")};

};



#endif //CATEGORYMODEL_H
