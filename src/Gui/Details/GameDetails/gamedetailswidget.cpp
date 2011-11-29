#include "gamedetailswidget.h"
#include "ui_gamedetailswidget.h"

#include <Database/database.h>
#include <Database/game.h>
#include <Database/place.h>
#include <Database/player.h>
#include <Gui/Misc/placescombobox.h>
#include <Misc/handler.h>

using namespace Gui::Details;

GameDetailsWidget::GameDetailsWidget(Database::Game* game, QWidget *parent) :
    DetailsWidget(game,parent),
    ui(new Ui::GameWidget),
    m_game(game),
    m_placesComboBox(new Misc::PlacesComboBox(this))
{
    ui->setupUi(this);
    ui->horizontalLayoutResidence->addWidget(m_placesComboBox);

    m_mayBeEditable = true;
    setEditable(false);

    connect(m_placesComboBox,SIGNAL(currentIndexChanged(Database::Place*const,Database::Place*const)),
	    this,SLOT(onPlacesComboBoxCurrentIndexChanged(Database::Place*const,Database::Place*const)));

    connectToAttributes();
    readData();
}

void GameDetailsWidget::readData(){
    if(m_game->site->value())
    {
        m_placesComboBox->setCurrentPlace(m_game->site->value()->id());
    }

    ui->textEditComment->setText(m_game->comment->value());
}

void GameDetailsWidget::connectToAttributes(){
    m_game->date->futureWatcher()->connectTo(ui->labelDateValue);
    m_game->length->futureWatcher()->connectTo(ui->labelLengthValue);
    m_game->site->futureWatcher()->connectTo(ui->labelResidenceValue);
    m_game->type->futureWatcher()->connectTo(ui->labelTypeValue);
    m_game->name->futureWatcher()->connectTo(ui->lineEditName);
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

void GameDetailsWidget::onPlacesComboBoxCurrentIndexChanged(Database::Place *const /*oldPlace*/ , Database::Place *const place)
{
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
    m_game->comment->setValue(ui->textEditComment->toPlainText());
}

void GameDetailsWidget::on_lineEditName_editingFinished()
{
    m_game->name->setValue(ui->lineEditName->text());
    readData();
}
