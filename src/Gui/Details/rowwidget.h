#ifndef ROWWIDGET_H
#define ROWWIDGET_H

#include <QWidget>
#include <QPointer>

namespace Database{

    class PSRow;

}

namespace Gui{

namespace Details{

class DetailsWidget;
class StatsWidget;

class RowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RowWidget(Database::PSRow* row, QWidget *parent = 0);

    Gui::Details::DetailsWidget * detailsWidget() const;
    Gui::Details::StatsWidget * statsWidget() const;

protected:
    Database::PSRow* m_row;
    DetailsWidget* m_detailsWidget;
    StatsWidget* m_statsWidget;

};

}}

#endif // ROWWIDGET_H
