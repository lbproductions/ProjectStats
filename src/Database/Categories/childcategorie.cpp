#include "childcategorie.h"

#include "parentcategorie.h"
#include "../categorie.h"

#include <QIcon>

using namespace Database;

START_ROW_IMPLEMENTATION(ChildCategorie, Categorie, Categorie)
{
    IMPLEMENT_ATTRIBUTE(QPointer<ParentCategorie>,ChildCategorie,parentCategorie,tr("ParentCategorie"))
}

QString ChildCategorie::mimeType() const
{
    return "application/projectstats.childCategorie";
}

QPointer<ParentCategorie> ChildCategorie::calculate_parentCategorie()
{        
        int id = -1;
        for(int i = 0; i<Categories::instance()->allRows().size();i++){
            if(Categories::instance()->allRows().at(i)->parentId->value() == m_id){
                id = Categories::instance()->allRows().at(i)->id();
            }
        }
        return (ParentCategorie*)Categories::instance()->rowById(id).data();

}

Models::TableModelBase* ChildCategorie::model()
{
    return 0;
}

Gui::MainWindow::Views::View *ChildCategorie::view()
{
    return 0;
}

END_ROW_IMPLEMENTATION()
