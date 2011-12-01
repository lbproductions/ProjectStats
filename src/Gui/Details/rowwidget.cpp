#include "rowwidget.h"

#include "detailswidget.h"
#include "statswidget.h"

#include <LBDatabase/LBDatabase.h>

#include <QSplitter>
#include <QVBoxLayout>


using namespace Gui::Details;

RowWidget::RowWidget(Database::Row* row, QWidget *parent) :
    QWidget(parent),
    m_row(row)
{
    QPalette p = palette();
    p.setColor(QPalette::Window, QColor(255,255,255));
    setPalette(p);

    m_detailsWidget = static_cast<Gui::Details::DetailsWidget*>(row->detailsWidget());
    m_statsWidget = static_cast<Gui::Details::StatsWidget*>(row->statsWidget());

    QSplitter* splitter = new QSplitter(this);
    if (m_detailsWidget != 0){
	splitter->addWidget(m_detailsWidget);
    }
    if (m_statsWidget != 0){
	splitter->addWidget(m_statsWidget);
    }

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(splitter);
    this->setLayout(layout);
}

Gui::Details::DetailsWidget *RowWidget::detailsWidget() const
{
    return m_detailsWidget;
}

Gui::Details::StatsWidget *RowWidget::statsWidget() const
{
    return m_statsWidget;
}
