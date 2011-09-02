#include "newrowwidget.h"
#include "ui_newrowwidget.h"

#include <Gui/Details/detailswidget.h>
#include <Database/table.h>

#include <QScrollArea>

NewRowWidget::NewRowWidget(Database::Row* row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRowWidget)
{
    ui->setupUi(this);

    m_row = row;

    setWindowModality(Qt::WindowModal);

    QPalette p = ui->scrollArea->palette();
    p.setColor(QPalette::Base, QColor(255,255,255,255));
    ui->scrollArea->setPalette(p);
    ui->scrollArea->setBackgroundRole(QPalette::Base);
    ui->scrollArea->setFrameShape(QFrame::Panel);
    ui->scrollArea->setAttribute(Qt::WA_MacShowFocusRect, false);

    Gui::Details::DetailsWidget *detailsWidget = row->detailsWidget();
    detailsWidget->setEditable(true);
    detailsWidget->setParent(this);
    ui->scrollArea->setWidget(detailsWidget);

    ui->labelDescription->setText(detailsWidget->description());

    ui->labelTitle->setText(detailsWidget->title());

    this->setMinimumHeight(detailsWidget->sizeHint().height()+160);

    setAttribute(Qt::WA_DeleteOnClose);
}

NewRowWidget::~NewRowWidget()
{
    delete ui;
}

void NewRowWidget::on_pushButtonCreate_clicked()
{
    m_row->table()->insertRow(m_row);
    this->accept();
}

void NewRowWidget::on_pushButtonCancel_clicked()
{
    this->reject();
}
