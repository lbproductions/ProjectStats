#ifndef FOLDERCATEGORIE_H
#define FOLDERCATEGORIE_H

#include "childcategorie.h"
#include "../listattribute.h"

class QMimeData;

namespace Database
{

class FolderCategorie : public ChildCategorie
{
    Q_OBJECT
public:
    virtual bool acceptMimeTypes(const QStringList &mimeTypes);
    virtual void dropMimeData(const QMimeData *data);

signals:
    void rowInserted(::Database::Row*);
    void rowRemoved(::Database::Row*);

protected:
    DECLARE_LISTATTRIBUTE(int,FolderCategorie,rows)

    void insertRow(Row *row);
    void removeRow(Row *row);

    FolderCategorie(int id, Categories *table);
};

}

#endif // FOLDERCATEGORIE_H
