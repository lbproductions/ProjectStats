#ifndef ROWWIDGET_H
#define ROWWIDGET_H

#include <QWidget>
#include <QPointer>

namespace Database{

    class Row;

}

namespace Gui{

namespace Details{

class DetailsWidget;
class StatsWidget;

class RowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RowWidget(Database::Row* row, QWidget *parent = 0);

    Gui::Details::DetailsWidget * detailsWidget() const;
    Gui::Details::StatsWidget * statsWidget() const;

protected:
    Database::Row* m_row;
    DetailsWidget* m_detailsWidget;
    StatsWidget* m_statsWidget;

};

}}

#endif // ROWWIDGET_H
