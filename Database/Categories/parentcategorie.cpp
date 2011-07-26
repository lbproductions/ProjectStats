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

AttributeList<ChildCategorie*> ParentCategorie::calculate_childCategories()
{
    QList<Categorie*> qlist = Categories::instance()->rowsBySqlCondition("WHERE parentId = "+QString::number(m_id)+" ORDER BY orderIndicator ASC");
    AttributeList<ChildCategorie*> list;
    foreach(Categorie* c, qlist){
        if(c)
        {
            list.append(static_cast<ChildCategorie*>(c));
        }
    }
    return list;
    /*
    while(select.next())
    {
	ChildCategorie *cc = qobject_cast<ChildCategorie*>(m_categories->categorieById(select.value(0).toInt()).data());
	if(cc != 0)
	{
	    list.append(cc);
	}
    }
    select.finish();
    return list;
    */
}

END_ROW_IMPLEMENTATION()
