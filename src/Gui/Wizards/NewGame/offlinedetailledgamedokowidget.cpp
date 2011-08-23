#include "offlinedetailledgamedokowidget.h"
#include "ui_offlinedetailledgamedokowidget.h"

#include "newgamewizard.h"

#include <Misc/handler.h>
#include <Database/player.h>
#include <Database/database.h>
#include <Database/place.h>
#include <Database/Doppelkopf/dokoofflinegame.h>
#include <Gui/Misc/placescombobox.h>

#include <QSpinBox>
#include <QMessageBox>

using namespace Gui::Wizards::NewGame;

OfflineDetailledGameDokoWidget::OfflineDetailledGameDokoWidget(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::OfflineDetailledGameDokoWidget)
{
    ui->setupUi(this);

    setupWidget(parent);

    this->setTitle(tr("Summary"));
}

OfflineDetailledGameDokoWidget::~OfflineDetailledGameDokoWidget()
{
    delete ui;
}

int OfflineDetailledGameDokoWidget::nextId() {
    if(getCorrectInput()){
        return NewGameWizard::Page_OfflineSummary;
    }
    else{
        return NewGameWizard::Page_DetailledOfflineDokoGame;
    }
}

void OfflineDetailledGameDokoWidget::setupWidget(QWidget *parent){
    m_placesComboBox = new Gui::Misc::PlacesComboBox(parent);
    ui->gridLayout_2->addWidget(m_placesComboBox,2,2);

    connect(ui->calendarWidgetDateGame,SIGNAL(clicked(QDate)),ui->dateEditGame,SLOT(setDate(QDate)));
    connect(ui->dateEditGame,SIGNAL(dateChanged(QDate)),ui->calendarWidgetDateGame,SLOT(setSelectedDate(QDate)));
    ui->dateEditGame->setDate(QDate().currentDate());
}

void OfflineDetailledGameDokoWidget::setPlayerNumberLayout(int number){

    m_playernumber = number;

    int compareRow = 1;
    while(compareRow<ui->gridLayoutPositions_2->rowCount()){
	if (ui->gridLayoutPositions_2->itemAtPosition(compareRow,0) != 0){
	    ui->gridLayoutPositions_2->itemAtPosition(compareRow,0)->widget()->setVisible(false);
	    ui->gridLayoutPositions_2->removeWidget(ui->gridLayoutPositions_2->itemAtPosition(compareRow,0)->widget());
	}
	if (ui->gridLayoutPositions_2->itemAtPosition(compareRow,1) != 0){
	    ui->gridLayoutPositions_2->itemAtPosition(compareRow,1)->widget()->setVisible(false);
	    ui->gridLayoutPositions_2->removeWidget(ui->gridLayoutPositions_2->itemAtPosition(compareRow,1)->widget());
	}
	if (ui->gridLayoutPositions_2->itemAtPosition(compareRow,2) != 0){
	    ui->gridLayoutPositions_2->itemAtPosition(compareRow,2)->widget()->setVisible(false);
	    ui->gridLayoutPositions_2->removeWidget(ui->gridLayoutPositions_2->itemAtPosition(compareRow,2)->widget());
	}
	if (ui->gridLayoutPositions_2->itemAtPosition(compareRow,3) != 0){
	    ui->gridLayoutPositions_2->itemAtPosition(compareRow,3)->widget()->setVisible(false);
	    ui->gridLayoutPositions_2->removeWidget(ui->gridLayoutPositions_2->itemAtPosition(compareRow,3)->widget());
	}
	if (ui->gridLayoutPositions_2->itemAtPosition(compareRow,4) != 0){
	    ui->gridLayoutPositions_2->itemAtPosition(compareRow,4)->widget()->setVisible(false);
	    ui->gridLayoutPositions_2->removeWidget(ui->gridLayoutPositions_2->itemAtPosition(compareRow,4)->widget());
	}
	if (ui->gridLayoutPositions_2->itemAtPosition(compareRow,5) != 0){
	    ui->gridLayoutPositions_2->itemAtPosition(compareRow,5)->widget()->setVisible(false);
	    ui->gridLayoutPositions_2->removeWidget(ui->gridLayoutPositions_2->itemAtPosition(compareRow,5)->widget());
	}
	compareRow++;
    }


    for (int i = 1; i<number+1;i++){
	QSpinBox* spinbox = new QSpinBox(this);
	spinbox->setValue(i);
	ui->gridLayoutPositions_2->addWidget(spinbox,i,0);

	QComboBox* comboBox = new QComboBox(this);

        foreach(Database::Player *player, Database::Players::instance()->allRows())
        {
            comboBox->addItem(player->name->value());
	}
	ui->gridLayoutPositions_2->addWidget(comboBox,i,1);

	QSpinBox* spinboxPoints = new QSpinBox(this);
	spinboxPoints->setValue(0);
	spinboxPoints->setMinimum(-150);
	spinboxPoints->setMaximum(150);
	ui->gridLayoutPositions_2->addWidget(spinboxPoints,i,2);

	QSpinBox* spinSoli = new QSpinBox(this);
	ui->gridLayoutPositions_2->addWidget(spinSoli,i,3);
	QSpinBox* spinHochzeit = new QSpinBox(this);
	ui->gridLayoutPositions_2->addWidget(spinHochzeit,i,4);
	QSpinBox* spinTrumpf = new QSpinBox(this);
	ui->gridLayoutPositions_2->addWidget(spinTrumpf,i,5);
    }

}

Database::Game* OfflineDetailledGameDokoWidget::saveGame(){
    if (ui->lineEditGameName->text() != "" && correctInput){

//	Database::Doppelkopf::DokoOfflineGame* game = static_cast<Database::Doppelkopf::DokoOfflineGame*>(Handler::getInstance()->database()->games()->createGame(ui->lineEditGameName->text(),false,DokoLiveGame::TYPE));
//	game->setType(ui->comboBoxGameResidence->currentText());
//	game->setComment(ui->textEditGameComment->toPlainText());
//	game->setSite(m_placesComboBox->currentPlace());
//	game->setDate(ui->dateEditGame->dateTime());
//	game->setType(DokoLiveGame::TYPE);

//	for (int i = 1; i<ui->gridLayoutPositions_2->rowCount();i++){
//	    int position = static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(i,0)->widget())->value();
//	    QString playername = static_cast<QComboBox*>(ui->gridLayoutPositions_2->itemAtPosition(i,1)->widget())->currentText();
//	    Database::Player* player = Handler::getInstance()->database()->players()->playerByName(playername);
//	    int points = static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(i,2)->widget())->value();
//	    game->addPlayer(player,position,points);
//	    int hochzeiten = static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(i,3)->widget())->value();
//	    game->setPlayerHochzeiten(player,hochzeiten);
//	    int soli = static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(i,4)->widget())->value();
//	    game->setPlayerSoli(player,soli);
//	    int trumpfabgaben = static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(i,5)->widget())->value();
//	    game->setPlayerTrumpfabgaben(player,trumpfabgaben);
//	}
//	return game;
    }

    return 0;
}

bool OfflineDetailledGameDokoWidget::checkInput(){
    if (ui->lineEditGameName->text() == ""){
	qDebug() << "OfflineDetailledGameDokoWidget::getCorrectInput(): No Game-Name";
	QMessageBox msg;
	msg.setText(tr("Please enter a name for this game."));
	msg.setInformativeText(tr("Every game needs a name, so that it can be identified more easily."));
	msg.setIcon(QMessageBox::Information);
	msg.exec();
	return false;
    }
    if (m_placesComboBox->currentText() == tr("Create new place...")){
	qDebug() << "OfflineDetailledGameDokoWidget::getCorrectInput(): No Place chosen";
	QMessageBox msg;
	msg.setText(tr("Please choose a site for this game."));
	msg.setInformativeText(tr("If you want statistics about how often you play at which place please enter a site.")+"<br>"
				+tr("If you don't want this, please create and choose a dummy place for this game."));
	msg.setIcon(QMessageBox::Information);
	msg.exec();
	return false;
    }
    for (int i = 1; i<ui->gridLayoutPositions_2->rowCount();i++){
	for (int j = 1; j<ui->gridLayoutPositions_2->rowCount();j++){
	    if (i != j){
		if (static_cast<QComboBox*>(ui->gridLayoutPositions_2->itemAtPosition(i,1)->widget())->currentText()
		    == static_cast<QComboBox*>(ui->gridLayoutPositions_2->itemAtPosition(j,1)->widget())->currentText())
		{
		    QString playerName = static_cast<QComboBox*>(ui->gridLayoutPositions_2->itemAtPosition(j,1)->widget())->currentText();
		    qDebug() << "OfflineDetailledGameDokoWidget::getCorrectInput(): Player "
			    + playerName
			    + " is double used";
		    QMessageBox msg;
		    msg.setText(tr("You used player ") + playerName + tr(" more than once."));
		    msg.setInformativeText(tr("Each player can only participate once in each game."));
		    msg.setIcon(QMessageBox::Information);
		    msg.exec();
		    return false;
		}
		if ((static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(i,0)->widget())->value() ==
		     static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(j,0)->widget())->value()) && (
			     static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(i,2)->widget())->value() !=
			     static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(j,2)->widget())->value())){
		    qDebug() << "OfflineDetailledGameDokoWidget::getCorrectInput(): Two Players has the same position, but different points";
		    QMessageBox msg;
		    msg.setText(tr("There are two players at the same position but have different points."));
		    msg.setInformativeText(tr("The player with more points should be in front of the other. Check your input!"));
		    msg.setIcon(QMessageBox::Information);
		    msg.exec();
		    return false;
		}
		if ((static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(i,0)->widget())->value() >
		     static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(j,0)->widget())->value()) && (
			     static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(i,2)->widget())->value() >
			     static_cast<QSpinBox*>(ui->gridLayoutPositions_2->itemAtPosition(j,2)->widget())->value())
		    ){
		    qDebug() << "OfflineDetailledGameDokoWidget::getCorrectInput(): One Player has a better position, but less points than another Player";
		    QMessageBox msg;
		    msg.setText(tr("There is a player who has more points than the other, but is in a worse position."));
		    msg.setInformativeText(tr("The player with more points should be in front of the other. Check your input!"));
		    msg.setIcon(QMessageBox::Information);
		    msg.exec();
		    return false;

		}

	    }
	}

    }
    return true;
}

bool OfflineDetailledGameDokoWidget::getCorrectInput(){
    correctInput = checkInput();
    return correctInput;
}
