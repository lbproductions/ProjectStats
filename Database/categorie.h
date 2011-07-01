#ifndef DATABASE_CATEGORIE_H
#define DATABASE_CATEGORIE_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

class QStandardItem;

namespace Database{
    class ParentCategorie;
}

START_ROW_DECLARATION(Categorie, Row)
    DECLARE_ROW_CONSTRUCTORS(Categorie, Categorie)

    /*!
      Gibt an, welchen Typ diese Kategorie hat.
      */
    enum CategorieType {
        ParentCategorieType, //!< Die Kategorie ist eine Überschrift in der Sidebar
        LibraryCategorieType, //!< Die Kategorie enthält alle Elemente einer Tabelle
        FolderCategorieType //!< Die Kategorie kann vom User befüllt werden
    };

    DECLARE_DATABASEATTRIBUTE(QString,Categorie,name)
    DECLARE_DATABASEATTRIBUTE(QString,Categorie,icon)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,parentId)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,type)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,orderIndicator)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,contentType)

    QStandardItem *standardItem() const;
    void setStandardItem(QStandardItem *item);

    bool isParentCategorie();

private:
    QStandardItem *m_standardItem;

END_ROW_DECLARATION(Categorie)

START_TABLE_DECLARATION(Categorie)
    QPointer<Categorie> createRowInstance(int id);
    QList<QPointer<ParentCategorie> > parentCategories();
END_TABLE_DECLARATION()

#endif // DATABASE_CATEGORIE_H
