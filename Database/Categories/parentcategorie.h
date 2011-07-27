#ifndef PARENTCATEGORIE_H
#define PARENTCATEGORIE_H

#include "../categorie.h"
#include <Database/listattribute.h>

START_ROW_DECLARATION(ParentCategorie, Categorie)
    DECLARE_ROW_CONSTRUCTORS(ParentCategorie, Categorie)
    /*!
      \return Alle Kinder dieser Kategorie. Die Liste müsste leer sein, falls der Typ dieser Kategorie ParentCategorieType ist.
      */
    DECLARE_LISTATTRIBUTE(ChildCategorie*,ParentCategorie,childCategories)

END_ROW_DECLARATION(ParentCategorie)

#endif // PARENTCATEGORIE_H
