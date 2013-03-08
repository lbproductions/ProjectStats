#include "summarywidget.h"

#include <Database/row.h>

namespace Gui {
namespace Details {


SummaryWidget::SummaryWidget(Database::Row *row, QWidget *parent):
    DetailsWidget(row,parent)
{
}

} // namespace Details
} // namespace Gui
