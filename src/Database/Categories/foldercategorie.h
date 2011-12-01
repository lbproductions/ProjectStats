#ifndef FOLDERCATEGORIE_H
#define FOLDERCATEGORIE_H

#include "childcategorie.h"

#include "../psrow.h"

class QMimeData;

START_ROW_DECLARATION(FolderCategorie, ChildCategorie)
    DECLARE_ROW_CONSTRUCTORS(FolderCategorie, ChildCategorie)

    virtual bool acceptMimeTypes(const QStringList &mimeTypes);
    virtual void dropMimeData(const QMimeData *data);

signals:
    void rowInserted(::Database::PSRow*);
    void rowRemoved(::Database::PSRow*);

protected:
    DECLARE_LISTATTRIBUTE(int,FolderCategorie,rows)

    void insertRow(Row *row);
    void removeRow(Row *row);

END_ROW_DECLARATION(FolderCategorie)


#endif // FOLDERCATEGORIE_H
