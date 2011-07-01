#include "gamedetailswidget.h"
#include "ui_gamedetailswidget.h"

#include <Database/database.h>
#include <Database/game.h>
#include <Database/place.h>
#include <Database/player.h>
#include <Gui/Misc/placescombobox.h>
#include <handler.h>

using namespace Gui::Details;

GameDetailsWidget::GameDetailsWidget(Database::Game* game, QWidget *parent) :
    DetailsWidget(game,parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);

    m_mayBeEditable = true;

    m_game = game;

    ui->formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

    m_placesComboBox = new Misc::PlacesComboBox(Database::Places::instance(),this);
    ui->horizontalLayoutResidence->addWidget(m_placesComboBox);

    setEditable(false);

    connect(m_placesComboBox,SIGNAL(currentIndexChanged(Database::Place*const,Database::Place*const)),
	    this,SLOT(onPlacesComboBoxCurrentIndexChanged(Database::Place*const,Database::Place*const)));
    readData();
}

void GameDetailsWidget::readData(){
    ui->labelDateValue->setText(m_game->date->value().toString("dd.MM.yyyy hh:mm:ss"));
    ui->labelLengthValue->setText(m_game->length->value().toString("hh:mm:ss"));
    ui->labelResidenceValue->setText(m_game->site->value()->displayString->value());
    ui->labelTypeValue->setText(m_game->type->value());
    ui->lineEditName->setText(m_game->name->value());
    m_placesComboBox->setCurrentPlace(m_game->site->value()->id());
    ui->textEditComment->setText(m_game->comment->value());
}

GameDetailsWidget::~GameDetailsWidget()
{
    delete ui;
}

void GameDetailsWidget::setEditable(bool editable)
{
    ui->lineEditName->setReadOnly(!editable);
    ui->lineEditName->setFrame(editable);
    ui->labelResidenceValue->setVisible(!editable);
    m_placesComboBox->setVisible(editable);
    ui->textEditComment->setReadOnly(!editable);

    readData();

    //workaround fuer darstellungsfehler
    resize(size().width()+1,size().height()+1);
    resize(size().width()-1,size().height()-1);
}

void GameDetailsWidget::onPlacesComboBoxCurrentIndexChanged(Database::Place *const /*oldPlace*/ , Database::Place *const place){
    Q_ASSERT(!m_game.isNull());

    if(place != 0)
    {
        m_game->siteId->setValue(place->id());
    }
    else
    {
        m_placesComboBox->setCurrentPlace(m_game->site->value()->id());
    }

    readData();
}

void GameDetailsWidget::on_textEditComment_textChanged()
{
    Q_ASSERT(!m_game.isNull());

    m_game->comment->setValue(ui->textEditComment->toPlainText());
}

void GameDetailsWidget::on_lineEditName_editingFinished()
{
    Q_ASSERT(!m_game.isNull());
    m_game->name->setValue(ui->lineEditName->text());
    readData();
}
