#ifndef GUI_DETAILS_SUMMARYWIDGET_H
#define GUI_DETAILS_SUMMARYWIDGET_H

#include <QWidget>

#include "detailswidget.h"

namespace Database{
    class Row;
}

namespace Gui {
namespace Details {

class SummaryWidget : public DetailsWidget
{
    Q_OBJECT
public:
    explicit SummaryWidget(Database::Row *row, QWidget *parent = 0);

signals:

public slots:

};

} // namespace Details
} // namespace Gui

#endif // GUI_DETAILS_SUMMARYWIDGET_H
