#include "foldercategorie.h"

#include <Models/tablemodel.h>
#include <Database/categorieassignment.h>

#include <QSqlQuery>
#include <QStringList>
#include <QDebug>

using namespace Database;

FolderCategorie::FolderCategorie(int id, Categories *table) :
    ChildCategorie(id,table)
{
    IMPLEMENT_LISTATTRIBUTE(int,FolderCategorie,rows,tr("Rows"))
}

AttributeList<int> FolderCategorie::calculate_rows()
{
    AttributeList<int> list;
    for(int i = 0; i<CategorieAssignments::instance()->allRows().size();i++){
        if(CategorieAssignments::instance()->allRows().at(i)->categorieId->value() == m_id){
            list.append(CategorieAssignments::instance()->allRows().at(i)->elementId->value());
        }
    }
    return list;
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
