#include "CategoryModel.h"

CategoryModel::CategoryModel(QObject* parent) : QAbstractListModel(parent)
{

}

QHash<int, QByteArray> CategoryModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[CategoryName] = "categoryName";
    roles[FilesRole] = "files";
    return roles;
}

QVariant CategoryModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid() || index.row() >= m_categories.size())
    {
        return {};
    }

    const auto category = m_categories.at(index.row());

    if(role == CategoryName)
    {
        return category.name;
    }
    if(role == FilesRole)
    {
        return QVariant::fromValue(category.files);
    }
    return {};
}

void CategoryModel::addCategory(const QString& categoryName)
{
    beginInsertRows(QModelIndex(), m_categories.size(), m_categories.size());
    m_categories << CategoryItem(categoryName);
    endInsertRows();
}

void CategoryModel::removeItem(int index)
{
    if(index < 0 || index >= m_categories.size())
    {
        return;
    }
    beginRemoveRows(QModelIndex(), index, index);
    m_categories.removeAt(index);
    endRemoveRows();
}

void CategoryModel::addNoteToCategory(int categoryIndex, const QString& noteName)
{
    m_categories[categoryIndex].files.append(File(noteName));
    QModelIndex modelIndex = createIndex(categoryIndex, 0);
    emit dataChanged(modelIndex, modelIndex, {FilesRole});
}

void CategoryModel::removeNoteFromCategory(int index, int noteIndex)
{
    qDebug() << index, " ",  noteIndex;
    m_categories[index].files.removeAt(noteIndex);
    QModelIndex modelIndex = createIndex(index, 0);
    emit dataChanged(modelIndex, modelIndex, {FilesRole});
}

int CategoryModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_categories.size();
}
