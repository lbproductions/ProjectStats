#include "smartfoldercategorie.h"

#include "leaguefoldercategorie.h"

#include <Database/categorieassignment.h>
#include <Database/Filters/rule.h>
#include <Gui/MainWindow/Views/ListView/listview.h>

using namespace Database;

SmartFolderCategorie::SmartFolderCategorie(int id, Categories *table) :
    ChildCategorie(id,table)
{
    initializeAttributes();
}

void SmartFolderCategorie::initializeAttributes()
{
    IMPLEMENT_ATTRIBUTE(Rule*, SmartFolderCategorie, filter, tr("filter"))
}

SmartFolderCategorie::SmartFolderCategorie() :
    ChildCategorie(0, Categories::instance())
{
    initializeAttributes();
}

SmartFolderCategorie::SmartFolderCategorie(LeagueFolderCategorie* /*parent*/) :
    ChildCategorie(0, Categories::instance())
{
    initializeAttributes();

    type->setValue(ChildCategorie::SmartFolderCategorieType);
}

QIcon SmartFolderCategorie::icon() const
{
    return QIcon(":/graphics/icons/mac/sidebar/sidebar_folder_smart");
}

Rule* SmartFolderCategorie::calculate_filter()
{
    QList<CategorieAssignment*> qlist = CategorieAssignments::instance()->rowsBySqlCondition("WHERE categorieId = "+QString::number(m_id));
    if(!qlist.isEmpty())
    {
        int filterId = qlist.at(0)->elementId->value();
        return Rules::instance()->castedRowById(filterId);
    }

    return 0;
}

void SmartFolderCategorie::setFilter(Rule* filter)
{
    CategorieAssignment* assign = new CategorieAssignment();
    assign->categorieId->setValue(m_id);
    assign->elementId->setValue(filter->id());
    connect(filter,SIGNAL(idChanged(int)),assign->elementId,SLOT(changeValue(int)));

    addChildRow(assign);
    addChildRow(filter);
}
