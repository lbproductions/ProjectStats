#include "categoriesmodel.h"

#include <Database/categorie.h>
#include <Database/Categories/parentcategorie.h>
#include <Database/Categories/childcategorie.h>
#include <Database/Categories/foldercategorie.h>

#include <QColor>
#include <QFont>
#include <QFileIconProvider>
#include <QIcon>
#include <QMimeData>

using namespace Models;

CategoriesModel::CategoriesModel(Database::Categories *categories) :
    QStandardItemModel(categories),
    m_categories(categories)
{
    QStandardItem* rootItem = this->invisibleRootItem();

    foreach(Database::ParentCategorie *p, m_categories->parentCategories())
    {
        QStandardItem *parentItem = createParentItem(p);
        if(p->name->value() == "My Folders")
        {
            m_folderParentItem = parentItem;
        }
        else if(p->name->value() == "Leagues")
        {
            m_leaguesParentItem = parentItem;
        }

	rootItem->appendRow(parentItem);

        for(int i = 0; i<p->childCategories->value().size();i++)
        {
            QStandardItem* childItem = createChildItem(p->childCategories->value(i));
            parentItem->appendRow(childItem);
        }

    }

    connect(m_categories,SIGNAL(rowInserted(::Database::PSRow*)),this,SLOT(on_folderCreated(::Database::PSRow*)));
}

void CategoriesModel::on_folderCreated(::Database::PSRow* row)
{
    Database::FolderCategorie* folder = static_cast<Database::FolderCategorie*>(row);
    if(folder == 0)
    {
        return;
    }

    QStandardItem *newFolder = createChildItem(folder);
    folder->setStandardItem(newFolder);

    if(folder->contentType->value() == Database::ChildCategorie::LeagueCategorieContentType)
    {
        m_leaguesParentItem->appendRow(newFolder);
        emit folderItemAdded(folder, newFolder);
    }
    else if(folder->parentId->value() == 5)
    {
        m_folderParentItem->appendRow(newFolder);
        emit folderItemAdded(folder, newFolder);
    }
}

QStandardItem *CategoriesModel::createParentItem(Database::ParentCategorie *p)
{
    QStandardItem* parentItem = new QStandardItem(p->name->value());
    parentItem->setData(QVariant::fromValue((void *) p));
    parentItem->setFlags(Qt::ItemIsEnabled);
    parentItem->setForeground(QBrush(QColor::fromRgb(112,129,147)));
    QFont f = parentItem->font();
    f.setFamily("Lucida Grande");
    f.setPixelSize(13);
    f.setBold(true);
    f.setCapitalization(QFont::AllUppercase);
    parentItem->setFont(f);
    parentItem->setSizeHint(QSize(0,18));

    p->setStandardItem(parentItem);

    return parentItem;
}

QStandardItem *CategoriesModel::createChildItem(Database::ChildCategorie *c)
{
    QStandardItem* childItem = new QStandardItem();
    childItem->setData(c->name->value(),Qt::UserRole + 2);
    childItem->setData(QVariant::fromValue((void *) c));

    QIcon icon = QIcon(c->icon->value());
    if(!icon.isNull())
    {
	childItem->setIcon(icon);
    }
    else
    {
	QFileIconProvider p;
	childItem->setIcon(p.icon(QFileIconProvider::Folder));
    }

    QFont f = childItem->font();
    f.setFamily("Lucida Grande");
    f.setPixelSize(13);
    childItem->setFont(f);

    childItem->setSizeHint(QSize(0,24));

    Qt::ItemFlags defaultFlags = childItem->flags();
    if(c->type->value() == Database::Categorie::FolderCategorieType)
    {
	defaultFlags = defaultFlags | Qt::ItemIsEditable | Qt::ItemIsDropEnabled;
	childItem->setDropEnabled(true);
    }

    childItem->setFlags(defaultFlags | Qt::ItemIsSelectable);

    c->setStandardItem(childItem);

    return childItem;
}

QStringList CategoriesModel::mimeTypes() const
{
    QStringList types;
    types << "application/projectstats.game";
    types << "application/projectstats.drink";
    types << "application/projectstats.player";
    types << "application/projectstats.place";
    return types;
}

Qt::DropActions CategoriesModel::supportedDropActions() const
{
    return Qt::CopyAction;
}

bool CategoriesModel::dropMimeData(const QMimeData */*data*/, Qt::DropAction /*action*/, int /*row*/, int /*column*/, const QModelIndex &/*parent*/)
{
    return true;
}
