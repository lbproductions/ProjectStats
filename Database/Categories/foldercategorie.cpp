#include "foldercategorie.h"

#include <Models/tablemodel.h>
#include <Database/categorieassignment.h>

#include <QSqlQuery>
#include <QStringList>
#include <QDebug>

START_ROW_IMPLEMENTATION(FolderCategorie, Categorie, ChildCategorie)
{
    IMPLEMENT_LISTATTRIBUTE(int,FolderCategorie,rows,tr("Rows"))
}

QList<int> FolderCategorie::calculate_rows()
{
    QList<int> list;
    for(int i = 0; i<CategorieAssignments::instance()->allRows().size();i++){
        if(CategorieAssignments::instance()->allRows().at(i)->categorieId->value() == m_id){
            list.append(CategorieAssignments::instance()->allRows().at(i)->elementId->value());
        }
    }
    return list;
}

QString FolderCategorie::mimeType() const
{
    return "application/projectstats.folderCategorie";
}

void FolderCategorie::insertRow(Row *row)
{
    if(row == 0 || !row->isValid())
    {
        return;
    }

    for(int i = 0; i<CategorieAssignments::instance()->allRows().size();i++){
        CategorieAssignment* as = CategorieAssignments::instance()->allRows().at(i);
        if(as->categorieId->value() == m_id || as->elementId->value() == row->id()){
            return;
        }
    }

    CategorieAssignment* assign = new CategorieAssignment();
    assign->categorieId->setValue(m_id);
    assign->elementId->setValue(row->id());
    CategorieAssignments::instance()->insertRow(assign);
}

void FolderCategorie::removeRow(Row *row)
{
    if(row == 0)
    {
	return;
    }
    CategorieAssignments::instance()->deleteRow(row);
}

bool FolderCategorie::acceptMimeTypes(const QStringList &mimeTypes)
{
    foreach(QString s, model()->mimeTypes())
    {
        if(mimeTypes.contains(s))
        {
            return true;
        }
    }

    return false;
}

void FolderCategorie::dropMimeData(const QMimeData */*data*/)
{
}

END_ROW_IMPLEMENTATION()
