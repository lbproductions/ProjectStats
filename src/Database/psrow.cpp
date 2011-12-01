#include "psrow.h"

#include <Gui/Details/rowwidget.h>

namespace Database {

PSRow::PSRow() :
    Row()
{
}

PSRow::PSRow(const PSRow &other) :
    Row(other)
{
}

PSRow::PSRow(int id, TableBase *table) :
    Row(id,table)
{
}

Gui::Details::DetailsWidget *PSRow::detailsWidget()
{
    return 0;
}

Gui::Details::RowWidget* PSRow::rowWidget()
{
    return new Gui::Details::RowWidget(this);
}

Gui::Details::RowWindow* PSRow::rowWindow()
{
    return 0;
}

Gui::Details::StatsWidget* PSRow::statsWidget()
{
    return 0;
}

Gui::Details::SummaryWidget* PSRow::summaryWidget()
{
    return 0;
}

}
