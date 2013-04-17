#include "newrounddialog.h"
#include "ui_newrounddialog.h"

#include <Database/Doppelkopf/dokoround.h>
#include <Database/Doppelkopf/dokolivegame.h>

#include <QFile>

namespace DokoLiveGameWindowNS {

NewRoundDialog::NewRoundDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRoundDialog),
    m_doppelkopfRound(0)
{
    ui->setupUi(this);

    this->layout()->setContentsMargins(0,0,0,0);

    setWindowFlags(Qt::FramelessWindowHint);

    ui->buttonGroup->setId(ui->pushButtonNormal, 0);
    ui->buttonGroup->setId(ui->pushButtonHochzeit, 1);
    ui->buttonGroup->setId(ui->pushButtonSolo, 2);
    ui->buttonGroup->setId(ui->pushButtonTrumpfabgabe, 3);

    this->setObjectName("dialog");
    this->setStyleSheet("QWidget#dialog { background-image: url(:/graphics/images/background_linen); } QLabel { color: white; }");

    QFile stylesheet2(":/graphics/styles/mac/pushbutton_iphotodarktab/stylesheet");
    stylesheet2.open(QFile::ReadOnly);
    QString style = stylesheet2.readAll();

    ui->pushButtonNormal->setStyleSheet(style);
    ui->pushButtonHochzeit->setStyleSheet(style);
    ui->pushButtonSolo->setStyleSheet(style);
    ui->pushButtonTrumpfabgabe->setStyleSheet(style + QLatin1String("QPushButton {margin-right: -5px; }"));

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
    connect(ui->comboBoxNormalRe1, SIGNAL(currentIndexChanged(int)), this, SLOT(checkNormalRoundContents()));
    connect(ui->comboBoxNormalRe2, SIGNAL(currentIndexChanged(int)), this, SLOT(checkNormalRoundContents()));
    connect(ui->spinBoxNormalPoints,SIGNAL(valueChanged(int)), this, SLOT(checkNormalRoundContents()));

    connect(ui->comboBoxHochzeitHochzeit, SIGNAL(currentIndexChanged(int)), this, SLOT(checkHochzeitRoundContents()));
    connect(ui->comboBoxHochzeitFellow, SIGNAL(currentIndexChanged(int)), this, SLOT(checkHochzeitRoundContents()));
    connect(ui->spinBoxHochzeitPoints,SIGNAL(valueChanged(int)),this, SLOT(checkHochzeitRoundContents()));

    connect(ui->comboBoxSoloPlayer, SIGNAL(currentIndexChanged(int)), this, SLOT(checkSoloRoundContents()));
    connect(ui->comboBoxSoloType, SIGNAL(currentIndexChanged(int)), this, SLOT(checkSoloRoundContents()));
    connect(ui->spinBoxSoloPoints,SIGNAL(valueChanged(int)), this, SLOT(checkSoloRoundContents()));

    connect(ui->comboBoxTrumpfabgabePlayer, SIGNAL(currentIndexChanged(int)), this, SLOT(checkTrumpfabgabeRoundContents()));
    connect(ui->comboBoxTrumpfabgabeAccept, SIGNAL(currentIndexChanged(int)), this, SLOT(checkTrumpfabgabeRoundContents()));
    connect(ui->spinBoxTrumpfabgabePoints,SIGNAL(valueChanged(int)),this, SLOT(checkTrumpfabgabeRoundContents()));

    connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(setCurrentPage(int)));

    connect(ui->buttonBox->button(QDialogButtonBox::Save), SIGNAL(clicked()), this, SLOT(save()));
}

NewRoundDialog::~NewRoundDialog()
{
    delete ui;
}

void NewRoundDialog::setDoppelkopfRound(Database::DokoRound *round)
{
    if(!round || m_doppelkopfRound == round)
        return;

    Database::DokoLiveGame *game = static_cast<Database::DokoLiveGame *>(round->game->value());

    m_doppelkopfRound = round;
    ui->comboBoxNormalRe1->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxNormalRe1->setCurrentPlayer(round->rePlayer1());
    ui->comboBoxNormalRe2->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxNormalRe2->setCurrentPlayer(round->rePlayer2());
    ui->comboBoxNormalSchweine->setEnabled(game->doko_mitSchweinerei->value());
    ui->comboBoxNormalSchweine->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxNormalSchweine->setCurrentPlayer(round->schweinereiPlayer());

    ui->comboBoxHochzeitHochzeit->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxHochzeitHochzeit->setCurrentPlayer(round->hochzeitPlayer());
    ui->comboBoxHochzeitFellow->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxHochzeitFellow->setCurrentPlayer(round->rePlayer2());
    ui->comboBoxHochzeitSchweine->setEnabled(game->doko_mitSchweinerei->value());
    ui->comboBoxHochzeitSchweine->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxHochzeitSchweine->setCurrentPlayer(round->schweinereiPlayer());

    ui->comboBoxSoloPlayer->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxSoloPlayer->setCurrentPlayer(round->dokoSoloPlayer());
    ui->comboBoxSoloSchweine->setEnabled(game->doko_mitSchweinerei->value());
    ui->comboBoxSoloSchweine->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxSoloSchweine->setCurrentPlayer(round->schweinereiPlayer());
    ui->comboBoxSoloHochzeit->setEnabled(game->doko_mitSchweinerei->value());
    ui->comboBoxSoloHochzeit->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxSoloHochzeit->setCurrentPlayer(round->schweinereiPlayer());
    ui->checkBoxSoloPflicht->setEnabled(game->doko_mitPflichtsolo->value());
    ui->comboBoxSoloType->addItems(game->allowedSoli());
    if(game->allowedSoli().indexOf(round->doko_soloType->value()) >= 0)
        ui->comboBoxSoloType->setCurrentIndex(game->allowedSoli().indexOf(round->doko_soloType->value()));
    else
        ui->comboBoxSoloType->setCurrentIndex(0);

    ui->comboBoxTrumpfabgabePlayer->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxTrumpfabgabePlayer->setCurrentPlayer(round->trumpfabgabePlayer());
    ui->comboBoxTrumpfabgabeAccept->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxTrumpfabgabeAccept->setCurrentPlayer(round->rePlayer2());
    ui->comboBoxTrumpfabgabeSchweine->setEnabled(game->doko_mitSchweinerei->value());
    ui->comboBoxTrumpfabgabeSchweine->addPlayers(round->currentPlayingPlayers->value());
    ui->comboBoxTrumpfabgabeSchweine->setCurrentPlayer(round->schweinereiPlayer());

    ui->pushButtonSolo->setEnabled(!game->allowedSoli().isEmpty());
    ui->pushButtonHochzeit->setEnabled(game->doko_mitHochzeit->value());
    ui->pushButtonTrumpfabgabe->setEnabled(game->doko_mitTrumpfabgabe->value());

    ui->comboBoxWinner->addItem("Re");
    ui->comboBoxWinner->addItem("Contra");

    ui->comboBoxTrumpfabgabeWinner->addItem("Re");
    ui->comboBoxTrumpfabgabeWinner->addItem("Contra");

    ui->comboBoxSoloWinner->addItem("Re");
    ui->comboBoxSoloWinner->addItem("Contra");

    ui->comboBoxHochzeitWinner->addItem("Re");
    ui->comboBoxHochzeitWinner->addItem("Contra");
}

void NewRoundDialog::setCurrentPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);

    switch(index) {
    case 0:
        checkNormalRoundContents();
        break;
    case 1:
        checkHochzeitRoundContents();
        break;
    case 2:
        checkSoloRoundContents();
        break;
    case 3:
        checkTrumpfabgabeRoundContents();
        break;
    default:
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
    }
}

void NewRoundDialog::checkNormalRoundContents()
{
    ui->comboBoxNormalRe1->addPlayers(m_doppelkopfRound->currentPlayingPlayers->value());
    ui->comboBoxNormalRe2->addPlayers(m_doppelkopfRound->currentPlayingPlayers->value());

    if(ui->comboBoxNormalRe1->currentPlayer()) {
        ui->comboBoxNormalRe2->removePlayer(ui->comboBoxNormalRe1->currentPlayer());
    }
    if(ui->comboBoxNormalRe2->currentPlayer()) {
        ui->comboBoxNormalRe1->removePlayer(ui->comboBoxNormalRe2->currentPlayer());
    }

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(ui->comboBoxNormalRe1->currentPlayer() &&
                                                              ui->comboBoxNormalRe2->currentPlayer());

    if(ui->spinBoxNormalPoints->value() == 0)
    {
        ui->comboBoxWinner->setEnabled(true);
    }
    else
    {
        ui->comboBoxWinner->setEnabled(false);

        if(ui->spinBoxNormalPoints->value() > 0)
        {
            ui->comboBoxWinner->setCurrentIndex(ui->comboBoxWinner->findText("Re"));
        }
        if(ui->spinBoxNormalPoints->value() < 0)
        {
            ui->comboBoxWinner->setCurrentIndex(ui->comboBoxWinner->findText("Contra"));
        }
    }
}

void NewRoundDialog::checkHochzeitRoundContents()
{
    ui->comboBoxHochzeitHochzeit->addPlayers(m_doppelkopfRound->currentPlayingPlayers->value());
    ui->comboBoxHochzeitFellow->addPlayers(m_doppelkopfRound->currentPlayingPlayers->value());

    if(ui->comboBoxHochzeitHochzeit->currentPlayer()) {
        ui->comboBoxHochzeitFellow->removePlayer(ui->comboBoxHochzeitHochzeit->currentPlayer());
    }
    if(ui->comboBoxHochzeitFellow->currentPlayer()) {
        ui->comboBoxHochzeitHochzeit->removePlayer(ui->comboBoxHochzeitFellow->currentPlayer());
    }

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(ui->comboBoxHochzeitHochzeit->currentPlayer() &&
                                                              ui->comboBoxHochzeitFellow->currentPlayer());

    if(ui->spinBoxHochzeitPoints->value() == 0)
    {
        ui->comboBoxHochzeitWinner->setEnabled(true);
    }
    else
    {
        ui->comboBoxHochzeitWinner->setEnabled(false);

        if(ui->spinBoxHochzeitPoints->value() > 0)
        {
            ui->comboBoxHochzeitWinner->setCurrentIndex(ui->comboBoxHochzeitWinner->findText("Re"));
        }
        if(ui->spinBoxHochzeitPoints->value() < 0)
        {
            ui->comboBoxHochzeitWinner->setCurrentIndex(ui->comboBoxHochzeitWinner->findText("Contra"));
        }
    }
}

void NewRoundDialog::checkSoloRoundContents()
{
    Database::DokoLiveGame *game = static_cast<Database::DokoLiveGame *>(m_doppelkopfRound->game->value());
    if(!game->doko_mitPflichtsolo->value() ||
            (ui->comboBoxSoloPlayer->currentPlayer() && game->doko_hasPflichtSolo->value(ui->comboBoxSoloPlayer->currentPlayer()))) {
        ui->checkBoxSoloPflicht->setChecked(false);
        ui->checkBoxSoloPflicht->setEnabled(false);
    }
    else {
        ui->checkBoxSoloPflicht->setChecked(true);
        ui->checkBoxSoloPflicht->setEnabled(true);
    }

    if(ui->comboBoxSoloType->currentText() == "Trumpf") {
        ui->comboBoxSoloSchweine->setEnabled(true);
        ui->comboBoxSoloHochzeit->setEnabled(true);
    }
    else {
        ui->comboBoxSoloSchweine->setEnabled(false);
        ui->comboBoxSoloHochzeit->setEnabled(false);
        ui->comboBoxSoloSchweine->setCurrentPlayer(0);
        ui->comboBoxSoloHochzeit->setCurrentPlayer(0);
    }

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(ui->comboBoxSoloPlayer->currentPlayer());

    if(ui->spinBoxSoloPoints->value() == 0)
    {
        ui->comboBoxSoloWinner->setEnabled(true);
    }
    else
    {
        ui->comboBoxSoloWinner->setEnabled(false);

        if(ui->spinBoxSoloPoints->value() > 0)
        {
            ui->comboBoxSoloWinner->setCurrentIndex(ui->comboBoxSoloWinner->findText("Re"));
        }
        if(ui->spinBoxSoloPoints->value() < 0)
        {
            ui->comboBoxSoloWinner->setCurrentIndex(ui->comboBoxSoloWinner->findText("Contra"));
        }
    }
}

void NewRoundDialog::checkTrumpfabgabeRoundContents()
{
    ui->comboBoxTrumpfabgabePlayer->addPlayers(m_doppelkopfRound->currentPlayingPlayers->value());
    ui->comboBoxTrumpfabgabeAccept->addPlayers(m_doppelkopfRound->currentPlayingPlayers->value());

    if(ui->comboBoxTrumpfabgabePlayer->currentPlayer()) {
        ui->comboBoxTrumpfabgabeAccept->removePlayer(ui->comboBoxTrumpfabgabePlayer->currentPlayer());
    }
    if(ui->comboBoxTrumpfabgabeAccept->currentPlayer()) {
        ui->comboBoxTrumpfabgabePlayer->removePlayer(ui->comboBoxTrumpfabgabeAccept->currentPlayer());
    }

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(ui->comboBoxTrumpfabgabePlayer->currentPlayer() &&
                                                              ui->comboBoxTrumpfabgabeAccept->currentPlayer());

    if(ui->spinBoxTrumpfabgabePoints->value() == 0)
    {
        ui->comboBoxTrumpfabgabeWinner->setEnabled(true);
    }
    else
    {
        ui->comboBoxTrumpfabgabeWinner->setEnabled(false);

        if(ui->spinBoxTrumpfabgabePoints->value() > 0)
        {
            ui->comboBoxTrumpfabgabeWinner->setCurrentIndex(ui->comboBoxTrumpfabgabeWinner->findText("Re"));
        }
        if(ui->spinBoxTrumpfabgabePoints->value() < 0)
        {
            ui->comboBoxTrumpfabgabeWinner->setCurrentIndex(ui->comboBoxTrumpfabgabeWinner->findText("Contra"));
        }
    }
}

void NewRoundDialog::save()
{
    switch(ui->buttonGroup->checkedId()) {
    case 0:
        saveNormalRound();
        break;
    case 1:
        saveHochzeitRound();
        break;
    case 2:
        saveSoloRound();
        break;
    case 3:
        saveTrumpfabgabeRound();
        break;
    default:
        break;
    }
    accept();
}

void NewRoundDialog::saveNormalRound()
{
    m_doppelkopfRound->doko_re1PlayerId->setValue(ui->comboBoxNormalRe1->currentPlayer()->id());
    m_doppelkopfRound->doko_re2PlayerId->setValue(ui->comboBoxNormalRe2->currentPlayer()->id());
    m_doppelkopfRound->comment->setValue(ui->textEditNormalComment->toPlainText());
    if(ui->comboBoxNormalSchweine->currentPlayer())
        m_doppelkopfRound->doko_schweinereiPlayerId->setValue(ui->comboBoxNormalSchweine->currentPlayer()->id());

    foreach(Database::Player *p, m_doppelkopfRound->currentPlayingPlayers->value()) {
        if(p == ui->comboBoxNormalRe1->currentPlayer() ||
                p == ui->comboBoxNormalRe2->currentPlayer()) {
            m_doppelkopfRound->addPoints(p, ui->spinBoxNormalPoints->value());
        }
        else {
            m_doppelkopfRound->addPoints(p, -ui->spinBoxNormalPoints->value());
        }
    }
    m_doppelkopfRound->setState(Database::Round::FinishedState);
    if(ui->comboBoxWinner->currentText() == "Re")
    {
        m_doppelkopfRound->doko_winner->setValue(Database::DokoRound::Re);
    }
    else
    {
        m_doppelkopfRound->doko_winner->setValue(Database::DokoRound::Contra);
    }

    Database::DokoLiveGame *game = static_cast<Database::DokoLiveGame *>(m_doppelkopfRound->game->value());
    game->startNextRound();
}

void NewRoundDialog::saveHochzeitRound()
{
    m_doppelkopfRound->doko_hochzeitPlayerId->setValue(ui->comboBoxHochzeitHochzeit->currentPlayer()->id());
    m_doppelkopfRound->doko_re1PlayerId->setValue(ui->comboBoxHochzeitHochzeit->currentPlayer()->id());
    m_doppelkopfRound->doko_re2PlayerId->setValue(ui->comboBoxHochzeitFellow->currentPlayer()->id());
    m_doppelkopfRound->comment->setValue(ui->textEditHochzeitComment->toPlainText());
    if(ui->comboBoxHochzeitSchweine->currentPlayer())
        m_doppelkopfRound->doko_schweinereiPlayerId->setValue(ui->comboBoxHochzeitSchweine->currentPlayer()->id());

    foreach(Database::Player *p, m_doppelkopfRound->currentPlayingPlayers->value()) {
        if(p == ui->comboBoxHochzeitHochzeit->currentPlayer() ||
                p == ui->comboBoxHochzeitFellow->currentPlayer()) {
            m_doppelkopfRound->addPoints(p, ui->spinBoxHochzeitPoints->value());
        }
        else {
            m_doppelkopfRound->addPoints(p, -ui->spinBoxHochzeitPoints->value());
        }
    }
    m_doppelkopfRound->setState(Database::Round::FinishedState);

    if(ui->comboBoxWinner->currentText() == "Re")
    {
        m_doppelkopfRound->doko_winner->setValue(Database::DokoRound::Re);
    }
    else
    {
        m_doppelkopfRound->doko_winner->setValue(Database::DokoRound::Contra);
    }

    Database::DokoLiveGame *game = static_cast<Database::DokoLiveGame *>(m_doppelkopfRound->game->value());
    game->startNextRound();
}

void NewRoundDialog::saveSoloRound()
{
    m_doppelkopfRound->doko_soloPlayerId->setValue(ui->comboBoxSoloPlayer->currentPlayer()->id());
    m_doppelkopfRound->doko_re1PlayerId->setValue(ui->comboBoxSoloPlayer->currentPlayer()->id());
    m_doppelkopfRound->comment->setValue(ui->textEditSoloComment->toPlainText());
    if(ui->comboBoxSoloSchweine->currentPlayer())
        m_doppelkopfRound->doko_schweinereiPlayerId->setValue(ui->comboBoxSoloSchweine->currentPlayer()->id());
    if(ui->comboBoxSoloHochzeit->currentPlayer())
        m_doppelkopfRound->doko_hochzeitPlayerId->setValue(ui->comboBoxSoloHochzeit->currentPlayer()->id());
    m_doppelkopfRound->doko_soloType->setValue(ui->comboBoxSoloType->currentText());
    m_doppelkopfRound->doko_soloPflicht->setValue(ui->checkBoxSoloPflicht->isChecked());

    foreach(Database::Player *p, m_doppelkopfRound->currentPlayingPlayers->value()) {
        if(p == ui->comboBoxSoloPlayer->currentPlayer()) {
            m_doppelkopfRound->addPoints(p, 3 * ui->spinBoxSoloPoints->value());
        }
        else {
            m_doppelkopfRound->addPoints(p, -ui->spinBoxSoloPoints->value());
        }
    }
    m_doppelkopfRound->setState(Database::Round::FinishedState);

    if(ui->comboBoxWinner->currentText() == "Re")
    {
        m_doppelkopfRound->doko_winner->setValue(Database::DokoRound::Re);
    }
    else
    {
        m_doppelkopfRound->doko_winner->setValue(Database::DokoRound::Contra);
    }

    Database::DokoLiveGame *game = static_cast<Database::DokoLiveGame *>(m_doppelkopfRound->game->value());
    game->startNextRound();
    game->currentRound->value()->startTime->setValue(QDateTime::currentDateTime());
}

void NewRoundDialog::saveTrumpfabgabeRound()
{
    m_doppelkopfRound->doko_trumpfabgabePlayerId->setValue(ui->comboBoxTrumpfabgabePlayer->currentPlayer()->id());
    m_doppelkopfRound->doko_re1PlayerId->setValue(ui->comboBoxTrumpfabgabePlayer->currentPlayer()->id());
    m_doppelkopfRound->doko_re2PlayerId->setValue(ui->comboBoxTrumpfabgabeAccept->currentPlayer()->id());
    m_doppelkopfRound->comment->setValue(ui->textEditTrumpfabgabeComment->toPlainText());
    if(ui->comboBoxTrumpfabgabeSchweine->currentPlayer())
        m_doppelkopfRound->doko_schweinereiPlayerId->setValue(ui->comboBoxTrumpfabgabeSchweine->currentPlayer()->id());

    foreach(Database::Player *p, m_doppelkopfRound->currentPlayingPlayers->value()) {
        if(p == ui->comboBoxTrumpfabgabePlayer->currentPlayer() ||
                p == ui->comboBoxTrumpfabgabeAccept->currentPlayer()) {
            m_doppelkopfRound->addPoints(p, ui->spinBoxTrumpfabgabePoints->value());
        }
        else {
            m_doppelkopfRound->addPoints(p, -ui->spinBoxTrumpfabgabePoints->value());
        }
    }
    m_doppelkopfRound->setState(Database::Round::FinishedState);

    if(ui->comboBoxWinner->currentText() == "Re")
    {
        m_doppelkopfRound->doko_winner->setValue(Database::DokoRound::Re);
    }
    else
    {
        m_doppelkopfRound->doko_winner->setValue(Database::DokoRound::Contra);
    }

    Database::DokoLiveGame *game = static_cast<Database::DokoLiveGame *>(m_doppelkopfRound->game->value());
    game->startNextRound();
}

}

void DokoLiveGameWindowNS::NewRoundDialog::on_buttonBox_rejected()
{
    reject();
}
