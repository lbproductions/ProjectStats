#ifndef SMARTFOLDERCATEGORIE_H
#define SMARTFOLDERCATEGORIE_H

#include "childcategorie.h"
#include <Database/Filters/rule.h>

namespace Database
{

class LeagueFolderCategorie;
class Categories;

class SmartFolderCategorie : public ChildCategorie
{
    Q_OBJECT
public:
    SmartFolderCategorie();
    SmartFolderCategorie(LeagueFolderCategorie* );

    QIcon icon() const;

    template<class Type, class Table>
    QList<Type*> getAll();

    void setFilter(Rule* filter);

    DECLARE_ATTRIBUTE(Rule*, SmartFolderCategorie, filter)

friend class Categories;
private:
    SmartFolderCategorie(int id, Categories *table);

    void initializeAttributes();
};

template<class Type, class Table>
QList<Type*> SmartFolderCategorie::getAll()
{
    return filter->value()->getAll<Type,Table>();
}

}

Q_DECLARE_METATYPE(Database::SmartFolderCategorie)
Q_DECLARE_METATYPE(Database::SmartFolderCategorie*)
Q_DECLARE_METATYPE(QMap<Database::SmartFolderCategorie* COMMA int>)
Q_DECLARE_METATYPE(QList<Database::SmartFolderCategorie*>)
Q_DECLARE_METATYPE(QMap<int COMMA Database::SmartFolderCategorie*>)

#endif // SMARTFOLDERCATEGORIE_H
