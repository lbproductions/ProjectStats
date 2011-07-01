#include "childcategorie.h"

#include "parentcategorie.h"
#include "../categorie.h"

#include <QIcon>

using namespace Database;

ChildCategorie::ChildCategorie(int id, Categories *table) :
    Categorie(id,table)
{
    IMPLEMENT_ATTRIBUTE(ParentCategorie*,ChildCategorie,parentCategorie,tr("ParentCategorie"))
}

ParentCategorie *ChildCategorie::calculate_parentCategorie()
{        
        int id = -1;
        for(int i = 0; i<Categories::instance()->allRows().size();i++){
            if(Categories::instance()->allRows().at(i)->parentId->value() == m_id){
                id = Categories::instance()->allRows().at(i)->id();
            }
        }

        return qobject_cast<ParentCategorie*>(Categories::instance()->rowById(id));

}

Models::TableModelBase* ChildCategorie::model()
{
    return 0;
}

Gui::MainWindow::Views::View *ChildCategorie::view()
{
    return 0;
}
