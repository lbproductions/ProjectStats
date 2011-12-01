#include "endlivegamewidget.h"
#include "ui_endlivegamewidget.h"

#include <Database/player.h>

#include <QLineEdit>
#include <QTextEdit>

#include <Database/livegame.h>
#include <Database/place.h>
#include <Gui/Misc/groupbox.h>

#include <QDebug>

using namespace Gui::Details::LiveGameDetails;

EndLiveGameWidget::EndLiveGameWidget(Database::LiveGame* livegame, QWidget *parent) :
    QDialog(parent),
    m_livegame(livegame)
{
    m_nameLineEdit = new QLineEdit(this);
    m_nameLineEdit->setText(m_livegame->type->value() + " " + m_livegame->date->value().toString("dd.MM.yyyy") + " " + m_livegame->site->value()->ort->value());
    m_commentTextEdit = new QTextEdit(this);

    this->setWindowFlags(Qt::Sheet);

    setWindowModality(Qt::WindowModal);

    QPalette p(this->palette());
    p.setColor(QPalette::Background, QColor(55,55,55));
    this->setPalette(p);

    this->setStyleSheet("QFrame{margin: 0px; padding: 0px; background: transparent; color: white; border: none; font-weight: bold;}");
}

EndLiveGameWidget::~EndLiveGameWidget()
{
}

void EndLiveGameWidget::setupWidget(){
    this->setLayout(new QHBoxLayout(this));

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(tr("This is the end of your LiveGame! Please give it a name and - if you want - comment it."),this));
    layout->addWidget(m_nameLineEdit);
    layout->addWidget(m_commentTextEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    buttonLayout->addStretch();
    QPushButton* cancel = new QPushButton(tr("Cancel"),this);
    connect(cancel,SIGNAL(clicked()),this,SLOT(on_pushButtonCancel_clicked()));
    QPushButton* finish = new QPushButton(tr("Finish"),this);
    connect(finish,SIGNAL(clicked()),this,SLOT(on_pushButtonFinish_clicked()));
    buttonLayout->addWidget(cancel);
    buttonLayout->addWidget(finish);

    layout->addLayout(buttonLayout);

    Gui::Misc::GroupBox* box = new Gui::Misc::GroupBox(layout,this);
    this->layout()->addWidget(box);

    QGridLayout* players = new QGridLayout(this);
    players->addWidget(new QLabel(tr("Place"),this),0,0);
    players->addWidget(new QLabel(tr("Name"),this),0,1);
    players->addWidget(new QLabel(tr("Points"),this),0,2);
    players->addWidget(new QLabel(tr("AveragePlacement"),this),0,3);
    players->addWidget(new QLabel(tr("LeadingRounds"),this),0,4);

    int count = 1;
    foreach(Database::Player* p, m_livegame->playersSortedByPlacement->value()){
        players->addWidget(new QLabel(QString::number(m_livegame->placement->value(p))),count,0);
        players->addWidget(new QLabel(p->name->value()),count,1);
        players->addWidget(new QLabel(QString::number(m_livegame->points->value(p)),this),count,2,Qt::AlignCenter);
        players->addWidget(new QLabel(QString::number(m_livegame->averagePlacement->value(p)),this),count,3,Qt::AlignCenter);
        players->addWidget(new QLabel(QString::number(m_livegame->leadingRounds->value(p)),this),count,4,Qt::AlignCenter);

        addTypeSpecificInformation(players,count,5,p);

        count++;
    }

    Gui::Misc::GroupBox* stats = new Gui::Misc::GroupBox(players,this);
    this->layout()->addWidget(stats);

}

void EndLiveGameWidget::on_pushButtonFinish_clicked()
{
    m_livegame->name->setValue(m_nameLineEdit->text());
    m_livegame->comment->setValue(m_commentTextEdit->toPlainText());
    m_livegame->finishGame();

    this->accept();
}

void EndLiveGameWidget::on_pushButtonCancel_clicked()
{
    this->reject();
}

void EndLiveGameWidget::addTypeSpecificInformation(QGridLayout* layout, int row, int minColumn, Database::Player* player) {
    qDebug() << "EndLiveGameWidget::addTypeSpecificInformation";
}
