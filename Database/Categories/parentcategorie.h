#ifndef PARENTCATEGORIE_H
#define PARENTCATEGORIE_H

#include "../categorie.h"
#include <Database/listattribute.h>

namespace Database
{

class ChildCategorie;

class ParentCategorie : public Categorie
{
    Q_OBJECT
public:
    /*!
      \return Alle Kinder dieser Kategorie. Die Liste müsste leer sein, falls der Typ dieser Kategorie ParentCategorieType ist.
      */
    DECLARE_LISTATTRIBUTE(ChildCategorie*,ParentCategorie,childCategories)

friend class Categories;
private:
    ParentCategorie(int id, Categories *table);
};

}

#endif // PARENTCATEGORIE_H
