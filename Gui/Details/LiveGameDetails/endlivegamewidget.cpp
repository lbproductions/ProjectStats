#include "endlivegamewidget.h"
#include "ui_endlivegamewidget.h"

#include <Database/livegame.h>
#include <Database/place.h>

using namespace Gui::Details::LiveGameDetails;

EndLiveGameWidget::EndLiveGameWidget(Database::LiveGame* livegame, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndLiveGameWidget)
{
    ui->setupUi(this);

    m_livegame = livegame;

    ui->lineEditName->setText(m_livegame->type->value() + " " + m_livegame->date->value().toString("dd.MM.yyyy") + " " + m_livegame->site->value()->ort->value());

    this->setWindowFlags(Qt::Sheet);
}

EndLiveGameWidget::~EndLiveGameWidget()
{
    delete ui;
}

void EndLiveGameWidget::on_pushButtonFinish_clicked()
{
    m_livegame->name->setValue(ui->lineEditName->text());
    m_livegame->comment->setValue(ui->textEditComment->toPlainText());

    this->hide();
    emit liveGameClosed();
}

void EndLiveGameWidget::on_pushButtonCancel_clicked()
{
    this->hide();
}
