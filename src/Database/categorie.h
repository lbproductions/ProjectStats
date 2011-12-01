#ifndef DATABASE_CATEGORIE_H
#define DATABASE_CATEGORIE_H

#include "psrow.h"

class QStandardItem;

namespace Database{
    class ParentCategorie;
    class ChildCategorie;
}

START_ROW_DECLARATION(Categorie, PSRow)
    DECLARE_ROW_CONSTRUCTORS(Categorie, Categorie)

    /*!
      Gibt an, welchen Typ diese Kategorie hat.
      */
    enum CategorieType {
        ParentCategorieType, //!< Die Kategorie ist eine Überschrift in der Sidebar
        LibraryCategorieType, //!< Die Kategorie enthält alle Elemente einer Tabelle
        FolderCategorieType, //!< Die Kategorie kann vom User befüllt werden
        SmartFolderCategorieType
    };

    DECLARE_DATABASEATTRIBUTE(QString,Categorie,name)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,type)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,orderIndicator)

    QStandardItem *standardItem() const;
    void setStandardItem(QStandardItem *item);

    bool isParentCategorie();

private:
    QStandardItem *m_standardItem;

END_ROW_DECLARATION(Categorie)

START_TABLE_DECLARATION(Categorie)
    Categorie* createRowInstance(int id);
    QList<ParentCategorie* > parentCategories();
    QList<ChildCategorie*> childCategories(int parentId);
END_TABLE_DECLARATION()

#endif // DATABASE_CATEGORIE_H
