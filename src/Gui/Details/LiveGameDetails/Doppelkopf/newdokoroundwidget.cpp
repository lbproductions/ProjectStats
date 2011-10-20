#include "newdokoroundwidget.h"
#include "ui_newdokoroundwidget.h"

#include <Database/player.h>
#include <Database/database.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Misc/handler.h>
#include <Database/point.h>

#include <QFile>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

NewDokoRoundWidget::NewDokoRoundWidget(Database::DokoLiveGame* livegame, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDokoRoundWidget),
    m_livegame(livegame),
    m_round(0)
{
    initialize();
}

NewDokoRoundWidget::NewDokoRoundWidget(Database::DokoRound* round, Database::DokoLiveGame* livegame, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDokoRoundWidget),
    m_livegame(livegame),
    m_round(round)
{
    initialize();
    fillWidget();
}

void NewDokoRoundWidget::initialize()
{
    ui->setupUi(this);

    setupWidget();

    QPalette p(this->palette());
    p.setColor(QPalette::Background, QColor(55,55,55));
    this->setPalette(p);

    this->setStyleSheet("QGroupBox {"
                        "background: transparent;"
                        "border: 5px transparent;"
                        "border-image: url(:/graphics/styles/mac/groupbox/fullscreen/background) 5px 5px 5px 5px;"
                        "margin: 0px;"
                        "padding: -5px;"
                        "}"
                        "QLabel{color: white;}"
                        "QCheckBox{color:white;}");

    setWindowModality(Qt::WindowModal);
}

NewDokoRoundWidget::~NewDokoRoundWidget()
{
    delete ui;
}

void NewDokoRoundWidget::setupWidget()
{
    ui->comboBoxHochzeit->addItem("");
    ui->comboBoxRe1->addItem("");
    ui->comboBoxRe2->addItem("");
    ui->comboBoxSchweinerei->addItem("");
    ui->comboBoxSolo->addItem("");
    ui->comboBoxTrumpfabgabe->addItem("");

    foreach(Database::Player *player, m_livegame->currentPlayingPlayers->value())
    {
        ui->comboBoxHochzeit->addItem(QIcon(player->avatarPath->value()),player->name->value());
        ui->comboBoxRe1->addItem(QIcon(player->avatarPath->value()),player->name->value());
        ui->comboBoxRe2->addItem(QIcon(player->avatarPath->value()),player->name->value());
        ui->comboBoxSchweinerei->addItem(QIcon(player->avatarPath->value()),player->name->value());
        ui->comboBoxTrumpfabgabe->addItem(QIcon(player->avatarPath->value()),player->name->value());
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

    ui->comboBoxHochzeit->setVisible(m_livegame->doko_mitHochzeit->value());
    ui->labelHochzeit->setVisible(m_livegame->doko_mitHochzeit->value());

    ui->comboBoxSolo->setVisible(m_livegame->doko_mitSolo->value());
    ui->labelSolo->setVisible(m_livegame->doko_mitSolo->value());

    ui->comboBoxSchweinerei->setVisible(m_livegame->doko_mitSchweinerei->value());
    ui->labelSchweinerei->setVisible(m_livegame->doko_mitSchweinerei->value());

    ui->comboBoxTrumpfabgabe->setVisible(m_livegame->doko_mitTrumpfabgabe->value());
    ui->labelTrumpfabgabe->setVisible(m_livegame->doko_mitTrumpfabgabe->value());

    ui->checkBoxPflichtsolo->setVisible(m_livegame->doko_mitPflichtsolo->value());
    ui->checkBoxPflichtsolo->setChecked(m_livegame->doko_mitPflichtsolo->value());
}

void NewDokoRoundWidget::fillWidget()
{
    Database::Player* player = Database::Players::instance()->rowById(m_round->doko_hochzeitPlayerId->value());
    int index = 0;
    if(player)
    {
        index = ui->comboBoxHochzeit->findText(player->name->value());
    }
    ui->comboBoxHochzeit->setCurrentIndex(index);

    player = Database::Players::instance()->rowById(m_round->doko_re1PlayerId->value());
    index = 0;
    if(player)
    {
        index = ui->comboBoxRe1->findText(player->name->value());
    }
    ui->comboBoxRe1->setCurrentIndex(index);

    player = Database::Players::instance()->rowById(m_round->doko_re2PlayerId->value());
    index = 0;
    if(player)
    {
        index = ui->comboBoxRe2->findText(player->name->value());
    }
    ui->comboBoxRe2->setCurrentIndex(index);

    player = Database::Players::instance()->rowById(m_round->doko_schweinereiPlayerId->value());
    index = 0;
    if(player)
    {
        index = ui->comboBoxSchweinerei->findText(player->name->value());
    }
    ui->comboBoxSchweinerei->setCurrentIndex(index);

    player = Database::Players::instance()->rowById(m_round->doko_trumpfabgabePlayerId->value());
    index = 0;
    if(player)
    {
        index = ui->comboBoxTrumpfabgabe->findText(player->name->value());
    }
    ui->comboBoxTrumpfabgabe->setCurrentIndex(index);

    ui->comboBoxSolo->setCurrentIndex(ui->comboBoxSolo->findText(m_round->doko_soloType->value()));

//    foreach(Database::Player *player, m_livegame->currentPlayingPlayers->value())
//    {
//        ui->comboBoxHochzeit->addItem(QIcon(player->avatarPath->value()),player->name->value());
//        ui->comboBoxRe1->addItem(QIcon(player->avatarPath->value()),player->name->value());
//        ui->comboBoxRe2->addItem(QIcon(player->avatarPath->value()),player->name->value());
//        ui->comboBoxSchweinerei->addItem(QIcon(player->avatarPath->value()),player->name->value());
//        ui->comboBoxTrumpfabgabe->addItem(QIcon(player->avatarPath->value()),player->name->value());
//    }

//    ui->comboBoxWinner->addItem("Re");
//    ui->comboBoxWinner->addItem("Contra");

//    if(m_livegame->doko_mitBubensolo->value()){
//        ui->comboBoxSolo->addItem("Buben");
//    }
//    if(m_livegame->doko_mitDamensolo->value()){
//        ui->comboBoxSolo->addItem("Damen");
//    }
//    if(m_livegame->doko_mitFleischlos->value()){
//        ui->comboBoxSolo->addItem("Fleischlos");
//    }
//    if(m_livegame->doko_mitTrumpfsolo->value()){
//        ui->comboBoxSolo->addItem("Trumpf");
//    }
//    if(m_livegame->doko_mitFarbsolo->value()){
//        ui->comboBoxSolo->addItem("Farben");
//    }

//    ui->comboBoxHochzeit->setVisible(m_livegame->doko_mitHochzeit->value());
//    ui->labelHochzeit->setVisible(m_livegame->doko_mitHochzeit->value());

//    ui->comboBoxSolo->setVisible(m_livegame->doko_mitSolo->value());
//    ui->labelSolo->setVisible(m_livegame->doko_mitSolo->value());

//    ui->comboBoxSchweinerei->setVisible(m_livegame->doko_mitSchweinerei->value());
//    ui->labelSchweinerei->setVisible(m_livegame->doko_mitSchweinerei->value());

//    ui->comboBoxTrumpfabgabe->setVisible(m_livegame->doko_mitTrumpfabgabe->value());
//    ui->labelTrumpfabgabe->setVisible(m_livegame->doko_mitTrumpfabgabe->value());

//    ui->checkBoxPflichtsolo->setVisible(m_livegame->doko_mitPflichtsolo->value());
//    ui->checkBoxPflichtsolo->setChecked(m_livegame->doko_mitPflichtsolo->value());
}

void NewDokoRoundWidget::on_pushButtonCreateRound_clicked()
{
    if (checkInputs())
    {
        Database::DokoRound* round = 0;
        if(!m_round)
        {
            round = static_cast<Database::DokoRound*>(m_livegame->currentRound->value());
        }
        else
        {
            round = m_round;
        }

        // Kein Solo
        if (ui->comboBoxSolo->currentText().isEmpty())
        {
            Database::Player* re1 = Database::Players::instance()->playerByName(ui->comboBoxRe1->currentText());
            Database::Player* re2 = Database::Players::instance()->playerByName(ui->comboBoxRe2->currentText());

	    Database::Player* contra1 = 0;
	    Database::Player* contra2 = 0;

	    int contraCount = 0;
            foreach(Database::Player* player, m_livegame->currentPlayingPlayers->value())
            {
                if (player->name->value() != re1->name->value() && player->name->value() != re2->name->value())
                {
                    if (contraCount == 0)
                    {
                        contra1 = player;
		    }
                    if (contraCount == 1)
                    {
                        contra2 = player;
		    }
		    contraCount++;
		}
	    }

            round->doko_re1PlayerId->setValue(re1->id());
            round->doko_re2PlayerId->setValue(re2->id());

	    int points = ui->spinBoxPoints->value();
            if (ui->comboBoxWinner->currentText() != "Re")
            {
                points = -points;
            }

            if(!m_round)
            {
                round->addPoints(re1,points);
                round->addPoints(re2,points);
                round->addPoints(contra1,-points);
                round->addPoints(contra2,-points);
            }
            else
            {
                round->pointObjects->value(re1)->points->setValue(points);
                round->pointObjects->value(re2)->points->setValue(points);
                round->pointObjects->value(contra1)->points->setValue(-points);
                round->pointObjects->value(contra2)->points->setValue(-points);
            }

            if (ui->comboBoxHochzeit->currentText() != "")
            {
                round->doko_hochzeitPlayerId->setValue(re2->id());
	    }
            if (ui->comboBoxSchweinerei->currentText() != "")
            {
                round->doko_schweinereiPlayerId->setValue(Database::Players::instance()->playerByName(ui->comboBoxSchweinerei->currentText())->id());
	    }
            if (ui->comboBoxTrumpfabgabe->currentText() != "")
            {
                round->doko_trumpfabgabePlayerId->setValue(Database::Players::instance()->playerByName(ui->comboBoxTrumpfabgabe->currentText())->id());
	    }
	}
        // Solo
        else
        {
            Database::Player* re1 = Database::Players::instance()->playerByName(ui->comboBoxRe1->currentText());
	    Database::Player* contra1 = 0;
	    Database::Player* contra2 = 0;
	    Database::Player* contra3 = 0;

            int contraCount = 0;
            foreach(Database::Player *player, m_livegame->currentPlayingPlayers->value())
            {
                if (player->name->value() != re1->name->value())
                {
                    if (contraCount == 0)
                    {
                        contra1 = player;
		    }
                    if (contraCount == 1)
                    {
                        contra2 = player;
		    }
                    if (contraCount == 2)
                    {
                        contra3 = player;
		    }
		    contraCount++;
		}
	    }

            round->doko_re1PlayerId->setValue(re1->id());
            round->doko_soloPlayerId->setValue(re1->id());
            round->doko_soloType->setValue(ui->comboBoxSolo->currentText());
            round->doko_soloPflicht->setValue(ui->checkBoxPflichtsolo->isChecked());

	    int points = ui->spinBoxPoints->value();
            if (ui->comboBoxWinner->currentText() != "Re")
            {
                points = -points;
	    }
            if(!m_round)
            {
                round->addPoints(re1,3*points);
                round->addPoints(contra1,-points);
                round->addPoints(contra2,-points);
                round->addPoints(contra3,-points);
            }
            else
            {
                round->pointObjects->value(re1)->points->setValue(3*points);
                round->pointObjects->value(contra1)->points->setValue(-points);
                round->pointObjects->value(contra2)->points->setValue(-points);
                round->pointObjects->value(contra3)->points->setValue(-points);
            }
	}
        round->comment->setValue(ui->lineEditComment->text());

        if(!m_round)
        {
            m_livegame->startNextRound();
            m_livegame->currentRound->value()->startTime->setValue(QDateTime().currentDateTime());
        }
        this->accept();
   }
}

void NewDokoRoundWidget::on_comboBoxRe1_currentIndexChanged(QString name)
{
    if (name != "" && ui->comboBoxRe2->currentText() == "")
    {
	ui->comboBoxRe2->clear();
	ui->comboBoxRe2->addItem("");
        foreach(Database::Player *player, m_livegame->currentPlayingPlayers->value())
        {
            if (player->name->value() != name)
            {
                ui->comboBoxRe2->addItem(player->name->value());
	    }
	}
    }
    if (name != "" && ui->comboBoxSolo->currentText() != "")
    {
        if (m_livegame->doko_hasPflichtSolo->value(Database::Players::instance()->playerByName(name)))
        {
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
        foreach(Database::Player *player, m_livegame->currentPlayingPlayers->value())
        {
            if (player->name->value() != name){
                ui->comboBoxRe1->addItem(player->name->value());
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
        foreach(Database::Player *player, m_livegame->currentPlayingPlayers->value())
        {
            if (player->name->value() != name)
            {
                ui->comboBoxRe1->addItem(player->name->value());
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
