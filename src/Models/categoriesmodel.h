#ifndef CATEGORIESMODEL_H
#define CATEGORIESMODEL_H

#include <QStandardItemModel>
#include <QPointer>

namespace Database
{
    class Categories;
    class Categorie;
    class Row;
    class FolderCategorie;
    class ChildCategorie;
    class ParentCategorie;
}

namespace Models
{

class CategoriesModel : public QStandardItemModel
{
    Q_OBJECT
public:
    CategoriesModel(Database::Categories *categories);

    QStringList mimeTypes() const;
    Qt::DropActions supportedDropActions() const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

signals:
    void folderItemAdded(::Database::FolderCategorie*, QStandardItem*);

private slots:
    void on_folderCreated(::Database::Row * row);

private:
    Database::Categories* m_categories;
    QStandardItem *m_folderParentItem;
    QStandardItem *m_leaguesParentItem;

    QStandardItem *createParentItem(Database::ParentCategorie *categorie);
    QStandardItem *createChildItem(Database::ChildCategorie *categorie);
};

}

#endif // CATEGORIESMODEL_H
