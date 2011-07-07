#include "newskatroundwidget.h"
#include "ui_newskatroundwidget.h"

#include <Database/database.h>
#include <Database/players.h>
#include <Database/player.h>
#include <Database/Skat/skatround.h>

#include "handler.h"
#include "messagesystem.h"

using namespace Gui::Details::LiveGameDetails::SkatLiveGameDetails;

NewSkatRoundWidget::NewSkatRoundWidget(Database::Skat::SkatLiveGame* skatlivegame, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewSkatRoundWidget)
{
    ui->setupUi(this);

    m_skatlivegame = skatlivegame;

    foreach(Database::Player* p, m_skatlivegame->playersSortedByPosition()){
        ui->comboBoxSolist->addItem(p->name());
    }

    ui->comboBoxGameType->addItem("-");
    ui->comboBoxGameType->addItem("Farbgame");
    ui->comboBoxGameType->addItem("Grand");
    ui->comboBoxGameType->addItem("Nullgame");
    ui->comboBoxGameType->addItem("Ramschen");

    ui->comboBoxTrumpfFarbe->addItem("-");
    ui->comboBoxTrumpfFarbe->addItem("Kreuz");
    ui->comboBoxTrumpfFarbe->addItem("Pik");
    ui->comboBoxTrumpfFarbe->addItem("Herz");
    ui->comboBoxTrumpfFarbe->addItem("Karo");

    ui->comboBoxWinner->addItem("Solist");
    ui->comboBoxWinner->addItem("Contra");
}

NewSkatRoundWidget::~NewSkatRoundWidget()
{
    delete ui;
}

void Gui::Details::LiveGameDetails::SkatLiveGameDetails::NewSkatRoundWidget::on_comboBoxGameType_currentIndexChanged(QString type)
{
    if(ui->comboBoxGameType->currentText() != "-"){
        if (ui->comboBoxGameType->currentText() == "Ramschen"){
            ui->labelWinner->setVisible(false);
            ui->labelPoints->setVisible(false);
            ui->comboBoxWinner->setVisible(false);
            ui->label_2->setVisible(false);
            ui->label_3->setVisible(false);
            ui->spinBoxMultiplikator->setVisible(false);
            ui->labelBasicPoints->setVisible(false);
            ui->labelResultPoints->setVisible(false);

            while (ui->verticalLayoutRamsch->count() > 0)
            {
                ui->verticalLayoutRamsch->removeItem(ui->verticalLayoutRamsch->itemAt(0));
            }

            QHBoxLayout* layout = new QHBoxLayout();
            layout->addWidget(new QLabel("Player"));
            layout->addWidget(new QLabel("Points"));
            ui->verticalLayoutRamsch->addLayout(layout);

            QList<QPointer<Database::Player> > list = m_skatlivegame->playersSortedByPosition();
            for(int i = 0;i<list.size();i++){
                QHBoxLayout* hlayout = new QHBoxLayout();
                hlayout->addWidget(new QLabel(list.at(i)->name()));
                hlayout->addWidget(new QSpinBox());
                ui->verticalLayoutRamsch->addLayout(hlayout);
            }
        }
        else{
            ui->labelWinner->setVisible(true);
            ui->labelPoints->setVisible(true);
            ui->comboBoxWinner->setVisible(true);
            ui->label_2->setVisible(true);
            ui->label_3->setVisible(true);
            ui->spinBoxMultiplikator->setVisible(true);
            ui->labelBasicPoints->setVisible(true);
            ui->labelResultPoints->setVisible(true);

            while (ui->verticalLayoutRamsch->count() > 0)
            {
                ui->verticalLayoutRamsch->removeItem(ui->verticalLayoutRamsch->itemAt(0));
            }
        }
        if (ui->comboBoxGameType->currentText() == "Grand"){
            ui->comboBoxTrumpfFarbe->setEnabled(false);
            ui->labelBasicPoints->setText("24");
        }
        if (ui->comboBoxGameType->currentText() == "Nullgame"){
            ui->comboBoxTrumpfFarbe->setEnabled(false);
            ui->labelBasicPoints->setText("23");
        }
        if (ui->comboBoxGameType->currentText() == "Farbgame"){
            ui->comboBoxTrumpfFarbe->setEnabled(true);
        }
    }
    this->repaint();
    calculatePoints();
}

void Gui::Details::LiveGameDetails::SkatLiveGameDetails::NewSkatRoundWidget::on_comboBoxTrumpfFarbe_currentIndexChanged(QString color)
{
    if (ui->comboBoxTrumpfFarbe->currentText() != "-"){
        if (ui->comboBoxTrumpfFarbe->currentText() == "Kreuz"){
            ui->labelBasicPoints->setText("12");
        }
        if (ui->comboBoxTrumpfFarbe->currentText() == "Pik"){
            ui->labelBasicPoints->setText("11");
        }
        if (ui->comboBoxTrumpfFarbe->currentText() == "Herz"){
            ui->labelBasicPoints->setText("10");
        }
        if (ui->comboBoxTrumpfFarbe->currentText() == "Karo"){
            ui->labelBasicPoints->setText("9");
        }
    }

    calculatePoints();
}

void Gui::Details::LiveGameDetails::SkatLiveGameDetails::NewSkatRoundWidget::on_comboBoxWinner_currentIndexChanged(QString winner)
{
    if (ui->comboBoxWinner->currentText() == "Contra"){
        ui->spinBoxMultiplikator->setMinimum(2);
    }
    if (ui->comboBoxWinner->currentText() == "Solist"){
        ui->spinBoxMultiplikator->setMinimum(1);
    }
}

void NewSkatRoundWidget::calculatePoints(){
    ui->labelResultPoints->setText(QString::number(ui->labelBasicPoints->text().toInt()*ui->spinBoxMultiplikator->value()));
}

void Gui::Details::LiveGameDetails::SkatLiveGameDetails::NewSkatRoundWidget::on_spinBoxMultiplikator_valueChanged(int )
{
    calculatePoints();
}

void Gui::Details::LiveGameDetails::SkatLiveGameDetails::NewSkatRoundWidget::on_pushButtonCreateRound_clicked()
{
    if (checkInputs()){
        Database::Round *r = m_skatlivegame->currentRound();
        Q_ASSERT(r != 0);
        Database::Skat::SkatRound* round = static_cast<Database::Skat::SkatRound*>(r);
        Q_ASSERT(round != 0);

        if (ui->comboBoxGameType->currentText() == "Ramschen"){
            for (int i = 1; i<ui->verticalLayoutRamsch->count();i++){
                QHBoxLayout* layout = static_cast<QHBoxLayout*>(ui->verticalLayoutRamsch->itemAt(i)->layout());
                QLabel* name = static_cast<QLabel*>(layout->itemAt(0)->widget());
                Database::Player* player = Handler::getInstance()->database()->players()->playerByName(name->text());
                QSpinBox* points = static_cast<QSpinBox*>(layout->itemAt(1)->widget());
                round->setPoints(player,points->value());
            }
        }
        else{
            foreach(Database::Player* p, round->currentPlayingPlayers()){
                if (ui->comboBoxWinner->currentText() == "Solist"){
                    if (ui->comboBoxSolist->currentText() == p->name()){
                        round->setPoints(p,0);
                    }
                    else{
                        round->setPoints(p,ui->labelResultPoints->text().toInt());
                    }
                }
                if (ui->comboBoxWinner->currentText() == "Contra"){
                    if (ui->comboBoxSolist->currentText() == p->name()){
                        round->setPoints(p,ui->labelResultPoints->text().toInt());
                    }
                    else{
                        round->setPoints(p,0);
                    }
                }
            }
            round->setTrumpfColor(ui->comboBoxTrumpfFarbe->currentText());
            round->setSolist(Handler::getInstance()->database()->players()->playerByName(ui->comboBoxSolist->currentText()));
        }
        round->setGameType(ui->comboBoxGameType->currentText());
        round->setState(Database::Round::FinishedState);
        m_skatlivegame->createRound();
        m_skatlivegame->currentRound()->setStartTime(QDateTime().currentDateTime());
        emit roundCreated();
    }
}

bool NewSkatRoundWidget::checkInputs(){
    bool check = true;
    if (ui->comboBoxTrumpfFarbe->currentText() == "-" && ui->comboBoxGameType->currentText() == "Farbgame"){
        check = false;
        Handler::getInstance()->messageSystem()->showWarning("No FarbTrumpf","Please select a Farbtrumpf or another GameType");
    }
    if (ui->comboBoxGameType->currentText() == "-"){
        check = false;
        Handler::getInstance()->messageSystem()->showWarning("No GameType","Please select another GameType");
    }
    return check;

}
