#include "childcategorie.h"

#include "parentcategorie.h"
#include "../categorie.h"

#include <QIcon>

using namespace Database;

START_ROW_IMPLEMENTATION(ChildCategorie, Categorie, Categorie)
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,Categorie,icon,tr("Icon"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Categorie,parentId,tr("parentId"))
    IMPLEMENT_ATTRIBUTE(ParentCategorie*,ChildCategorie,parentCategorie,tr("ParentCategorie"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Categorie,contentType,tr("ContentType"))

    m_view = 0;
}

QString ChildCategorie::mimeType() const
{
    return "application/projectstats.childCategorie";
}

ParentCategorie* ChildCategorie::calculate_parentCategorie()
{
    return static_cast<ParentCategorie*>(Categories::instance()->rowById(parentId->value()));
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
