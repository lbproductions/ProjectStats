#include "newdokoroundwidget.h"
#include "ui_newdokoroundwidget.h"

#include <Database/player.h>
#include <Database/database.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <handler.h>

#include <QFile>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

NewDokoRoundWidget::NewDokoRoundWidget(Database::DokoLiveGame* livegame, QWidget *parent) :
        QDialog(parent),
	ui(new Ui::NewDokoRoundWidget)
{
    ui->setupUi(this);

    m_livegame = livegame;

    m_playerlist = m_livegame->currentPlayingPlayers->value();
    qDebug() << m_playerlist.size();

    setupWidget();

   setWindowModality(Qt::WindowModal);
}

NewDokoRoundWidget::~NewDokoRoundWidget()
{
    delete ui;
}

void NewDokoRoundWidget::setupWidget(){

    ui->comboBoxHochzeit->addItem("");
    ui->comboBoxRe1->addItem("");
    ui->comboBoxRe2->addItem("");
    ui->comboBoxSchweinerei->addItem("");
    ui->comboBoxSolo->addItem("");
    ui->comboBoxTrumpfabgabe->addItem("");

    for (int i = 0; i<m_playerlist.size();i++){
        ui->comboBoxHochzeit->addItem(m_playerlist.at(i)->name->value());
        ui->comboBoxRe1->addItem(m_playerlist.at(i)->name->value());
        ui->comboBoxRe2->addItem(m_playerlist.at(i)->name->value());
        ui->comboBoxSchweinerei->addItem(m_playerlist.at(i)->name->value());
        ui->comboBoxTrumpfabgabe->addItem(m_playerlist.at(i)->name->value());
    }

    ui->comboBoxWinner->addItem("Re");
    ui->comboBoxWinner->addItem("Contra");

    if(m_livegame->doko_mitBubensolo->value()){
        ui->comboBoxSolo->addItem("Buben");
    }
    if(m_livegame->doko_mitDamensolo->value()){
        ui->comboBoxSolo->addItem("Damen");
    }
    if(m_livegame->doko_mitFleischlos->value()){
        ui->comboBoxSolo->addItem("Fleischlos");
    }
    if(m_livegame->doko_mitTrumpfsolo->value()){
        ui->comboBoxSolo->addItem("Trumpf");
    }
    if(m_livegame->doko_mitFarbsolo->value()){
        ui->comboBoxSolo->addItem("Farben");
    }


    if (!m_livegame->doko_mitHochzeit->value()){
	ui->comboBoxHochzeit->setVisible(false);
	ui->labelHochzeit->setVisible(false);
    }
    if(!m_livegame->doko_mitSolo->value()){
       ui->comboBoxSolo->setVisible(false);
       ui->labelSolo->setVisible(false);
    }
    if(!m_livegame->doko_mitSchweinerei->value()){
	ui->comboBoxSchweinerei->setVisible(false);
	ui->labelSchweinerei->setVisible(false);
    }
    if(!m_livegame->doko_mitTrumpfabgabe->value()){
	ui->comboBoxTrumpfabgabe->setVisible(false);
	ui->labelTrumpfabgabe->setVisible(false);
    }
    if (!m_livegame->doko_mitPflichtsolo->value()){
        ui->checkBoxPflichtsolo->setVisible(false);
        ui->checkBoxPflichtsolo->setChecked(false);
    }
}

void NewDokoRoundWidget::on_pushButtonCreateRound_clicked()
{
    if (checkInputs()){
        Database::Round *r = m_livegame->currentRound->value();
	Q_ASSERT(r != 0);
        Database::DokoRound* round = static_cast<Database::DokoRound*>(r);
	Q_ASSERT(round != 0);

	if (ui->comboBoxSolo->currentText() == ""){
            Database::Player* re1 = Database::Players::instance()->playerByName(ui->comboBoxRe1->currentText());
            Database::Player* re2 = Database::Players::instance()->playerByName(ui->comboBoxRe2->currentText());

	    Database::Player* contra1 = 0;
	    Database::Player* contra2 = 0;

	    int contraCount = 0;
	    for (int i = 0; i<m_playerlist.size();i++){
                if (m_playerlist.at(i)->name->value() != re1->name->value() && m_playerlist.at(i)->name->value() != re2->name->value()){
		    if (contraCount == 0){
			contra1 = m_playerlist.at(i);
		    }
		    if (contraCount == 1){
			contra2 = m_playerlist.at(i);
		    }
		    contraCount++;
		}
	    }

            round->doko_re1PlayerId->setValue(re1->id());
            round->doko_re2PlayerId->setValue(re2->id());

	    int points = ui->spinBoxPoints->value();
            if (ui->comboBoxWinner->currentText() != "Re"){
                points = -points;
	    }

            round->points->setValue(re1,points);
            round->points->setValue(re2,points);
            round->points->setValue(contra1,-points);
            round->points->setValue(contra2,-points);

	    if (ui->comboBoxHochzeit->currentText() != ""){
                round->doko_hochzeitPlayerId->setValue(re2->id());
	    }
	    if (ui->comboBoxSchweinerei->currentText() != ""){
                round->doko_schweinereiPlayerId->setValue(Database::Players::instance()->playerByName(ui->comboBoxSchweinerei->currentText())->id());
	    }
	    if (ui->comboBoxTrumpfabgabe->currentText() != ""){
                round->doko_trumpfabgabePlayerId->setValue(Database::Players::instance()->playerByName(ui->comboBoxTrumpfabgabe->currentText())->id());
	    }
	}
	else{
            Database::Player* re1 = Database::Players::instance()->playerByName(ui->comboBoxRe1->currentText());
	    Database::Player* contra1 = 0;
	    Database::Player* contra2 = 0;
	    Database::Player* contra3 = 0;

	    int contraCount = 0;
	    for (int i = 0; i<m_playerlist.size();i++){
                if (m_playerlist.at(i)->name->value() != re1->name->value()){
		    if (contraCount == 0){
			contra1 = m_playerlist.at(i);
		    }
		    if (contraCount == 1){
			contra2 = m_playerlist.at(i);
		    }
		    if (contraCount == 2){
			contra3 = m_playerlist.at(i);
		    }
		    contraCount++;
		}
	    }

            round->doko_re1PlayerId->setValue(re1->id());
            round->doko_soloPlayerId->setValue(re1->id());
            round->doko_soloType->setValue(ui->comboBoxSolo->currentText());
            round->doko_soloPflicht->setValue(ui->checkBoxPflichtsolo->isChecked());

	    int points = ui->spinBoxPoints->value();
            if (ui->comboBoxWinner->currentText() != "Re"){
                points = -points;
	    }
            round->points->setValue(re1,3*points);
            round->points->setValue(contra1,-points);
            round->points->setValue(contra2,-points);
            round->points->setValue(contra3,-points);
	}
        round->comment->setValue(ui->lineEditComment->text());
        round->db_state->setValue(Database::Round::FinishedState);
        m_livegame->startNextRound();
        m_livegame->currentRound->value()->startTime->setValue(QDateTime().currentDateTime());
        emit roundCreated();
        this->reject();
   }
}

void NewDokoRoundWidget::on_comboBoxRe1_currentIndexChanged(QString name)
{
    if (name != "" && ui->comboBoxRe2->currentText() == ""){
	ui->comboBoxRe2->clear();
	ui->comboBoxRe2->addItem("");
	for (int i = 0; i<m_playerlist.size();i++){
            if (m_playerlist.at(i)->name->value() != name){
                ui->comboBoxRe2->addItem(m_playerlist.at(i)->name->value());
	    }
	}
    }
    if (name != "" && ui->comboBoxSolo->currentText() != ""){
        if (m_livegame->doko_hasPflichtSolo->value(Database::Players::instance()->playerByName(name))){
            ui->checkBoxPflichtsolo->setChecked(false);
            ui->checkBoxPflichtsolo->setCheckable(false);
        }
    }
}

void NewDokoRoundWidget::on_comboBoxRe2_currentIndexChanged(QString name)
{
    if (name != "" && ui->comboBoxRe1->currentText() == ""){
	ui->comboBoxRe1->clear();
	ui->comboBoxRe1->addItem("");
	for (int i = 0; i<m_playerlist.size();i++){
            if (m_playerlist.at(i)->name->value() != name){
                ui->comboBoxRe1->addItem(m_playerlist.at(i)->name->value());
	    }
	}
    }
}



void NewDokoRoundWidget::on_comboBoxHochzeit_activated(QString name)
{
    if (name != ""){
	if (ui->comboBoxSolo->currentText() == ""){
	    ui->labelRe1->setText("HochzeitTeammate");
	    ui->comboBoxRe2->setEnabled(false);
	    ui->labelRe2->setEnabled(false);

	    if (ui->comboBoxRe2->findText(name) != -1){
		ui->comboBoxRe2->setCurrentIndex(ui->comboBoxRe2->findText(name));
	    }
	    else{
		ui->comboBoxRe2->addItem(name);
	    }

	    ui->comboBoxRe1->removeItem(ui->comboBoxRe1->findText(name));

	    ui->labelSolo->setEnabled(false);
	    ui->comboBoxSolo->setEnabled(false);
	    ui->comboBoxSolo->setCurrentIndex(ui->comboBoxSolo->findText(""));

	    ui->labelTrumpfabgabe->setEnabled(false);
	    ui->comboBoxTrumpfabgabe->setEnabled(false);
	    ui->comboBoxTrumpfabgabe->setCurrentIndex(ui->comboBoxTrumpfabgabe->findText(""));
	}
    }
    else{
	ui->labelRe1->setText("Re1");
	ui->labelRe2->setText("Re2");

	ui->comboBoxRe2->setEnabled(true);
	ui->labelRe2->setEnabled(true);

	ui->labelSolo->setEnabled(true);
	ui->comboBoxSolo->setEnabled(true);

	ui->labelSolo->setEnabled(true);
	ui->comboBoxTrumpfabgabe->setEnabled(true);

	ui->comboBoxRe1->clear();
	ui->comboBoxRe1->addItem("");
	for (int i = 0; i<m_playerlist.size();i++){
            if (m_playerlist.at(i)->name->value() != name){
                ui->comboBoxRe1->addItem(m_playerlist.at(i)->name->value());
	    }
	}

    }
}

void NewDokoRoundWidget::on_comboBoxSolo_currentIndexChanged(QString name)
{
    if (name != ""){
	ui->comboBoxRe2->setEnabled(false);
	ui->labelRe2->setEnabled(false);
	ui->comboBoxRe2->setCurrentIndex(ui->comboBoxRe2->findText(""));
	ui->labelRe1->setText("SoloPlayer");

	ui->labelTrumpfabgabe->setEnabled(false);
	ui->comboBoxTrumpfabgabe->setEnabled(false);
	ui->comboBoxTrumpfabgabe->setCurrentIndex(ui->comboBoxTrumpfabgabe->findText(""));

	if (name != "Trumpf"){
	    ui->labelSchweinerei->setEnabled(false);
	    ui->comboBoxSchweinerei->setEnabled(false);
	    ui->comboBoxSchweinerei->setCurrentIndex(ui->comboBoxSchweinerei->findText(""));

	    ui->labelHochzeit->setEnabled(false);
	    ui->comboBoxHochzeit->setEnabled(false);
	    ui->comboBoxHochzeit->setCurrentIndex(ui->comboBoxHochzeit->findText(""));
	}
	else{
	    ui->labelSchweinerei->setEnabled(true);
	    ui->comboBoxSchweinerei->setEnabled(true);

	    ui->labelHochzeit->setEnabled(true);
	    ui->comboBoxHochzeit->setEnabled(true);
	}

        if (ui->comboBoxRe1->currentText() != ""){
            if (m_livegame->doko_hasPflichtSolo->value(Database::Players::instance()->playerByName(ui->comboBoxRe1->currentText()))){
                ui->checkBoxPflichtsolo->setChecked(false);
                ui->checkBoxPflichtsolo->setCheckable(false);
            }
        }
    }
    else{
	ui->comboBoxRe2->setEnabled(true);
	ui->labelRe2->setEnabled(true);
	ui->labelRe1->setText("Re1");

	ui->labelTrumpfabgabe->setEnabled(true);
	ui->comboBoxTrumpfabgabe->setEnabled(true);

	ui->labelSchweinerei->setEnabled(true);
	ui->comboBoxSchweinerei->setEnabled(true);

	ui->labelHochzeit->setEnabled(true);
	ui->comboBoxHochzeit->setEnabled(true);
    }
}

void NewDokoRoundWidget::on_comboBoxTrumpfabgabe_currentIndexChanged(QString name)
{
    if (name != ""){
	ui->labelHochzeit->setEnabled(false);
	ui->comboBoxHochzeit->setEnabled(false);
	ui->comboBoxHochzeit->setCurrentIndex(ui->comboBoxHochzeit->findText(""));

	ui->labelSolo->setEnabled(false);
	ui->comboBoxSolo->setEnabled(false);
	ui->comboBoxSolo->setCurrentIndex(ui->comboBoxSolo->findText(""));

	ui->comboBoxRe2->setEnabled(false);
	if (ui->comboBoxRe2->findText(name) != -1){
	    ui->comboBoxRe2->setCurrentIndex(ui->comboBoxRe2->findText(name));
	}
	else{
	    ui->comboBoxRe2->addItem(name);
	}
	ui->labelRe2->setEnabled(false);
	ui->labelRe1->setText("TrumpfabgabenTaker");
    }
    else{

	ui->labelHochzeit->setEnabled(true);
	ui->comboBoxHochzeit->setEnabled(true);

	ui->labelSolo->setEnabled(true);
	ui->comboBoxSolo->setEnabled(true);

	ui->comboBoxRe2->setEnabled(true);
	ui->labelRe2->setEnabled(true);
	ui->labelRe1->setText("Re1");
    }
}

bool NewDokoRoundWidget::checkInputs(){
    if (ui->comboBoxRe1->currentText() == ui->comboBoxRe2->currentText()){
	qDebug() << "NewDokoRoundWidget:: Re1 = Re2!";
	return false;
    }
    if (ui->comboBoxHochzeit->currentText() == "" && ui->comboBoxSolo->currentText() == "" && ui->comboBoxTrumpfabgabe->currentText() == ""
	    && (ui->comboBoxRe1->currentText() == "" || ui->comboBoxRe2->currentText() == "")){
	qDebug() << "NewDokoRoundWidget:: Re1 or Re2 not selected";
	return false;
    }
    return true;
}

void Gui::Details::LiveGameDetails::DokoLiveGameDetails::NewDokoRoundWidget::on_pushButtonClose_clicked()
{
    this->reject();
}
