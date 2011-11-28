#include "parentcategorie.h"

#include "../categorie.h"
#include "childcategorie.h"


START_ROW_IMPLEMENTATION(ParentCategorie, Categorie, Categorie)
{
    IMPLEMENT_LISTATTRIBUTE(ChildCategorie*,ParentCategorie,childCategories,tr("ChildCategories"))
}

QString ParentCategorie::mimeType() const
{
    return "application/projectstats.parentCategorie";
}

QList<ChildCategorie*> ParentCategorie::calculate_childCategories()
{
    QList<Categorie*> qlist = Categories::instance()->rowsBySqlCondition("WHERE parentId = "+QString::number(m_id)+" ORDER BY orderIndicator ASC");
    QList<ChildCategorie*> list;
    foreach(Categorie* c, qlist){
        if(c)
        {
            list.append(static_cast<ChildCategorie*>(c));
        }
    }
    return list;
}

END_ROW_IMPLEMENTATION()
