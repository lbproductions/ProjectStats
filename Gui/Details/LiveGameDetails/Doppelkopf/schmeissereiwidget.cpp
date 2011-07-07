#include "schmeissereiwidget.h"
#include "ui_schmeissereiwidget.h"

#include <Database/Doppelkopf/dokoround.h>
#include <Database/database.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/player.h>
#include <handler.h>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

SchmeissereiWidget::SchmeissereiWidget(Database::DokoLiveGame* livegame, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchmeissereiWidget)
{
    ui->setupUi(this);

    m_livegame = livegame;

    if (m_livegame->doko_mitFuenfKoenige->value()){
        ui->comboBoxType->addItem(QString::fromUtf8("5 Könige"));
    }
    if (m_livegame->doko_mitZuWenigTrumpf->value()){
        ui->comboBoxType->addItem("Zu wenig Trumpf");
    }
    if (m_livegame->doko_mitTrumpfabgabeSchmeisserei->value()){
        ui->comboBoxType->addItem("Trumpfabgabe nicht genommen");
    }
    if (m_livegame->doko_mitNeunzigPunkte->value()){
        ui->comboBoxType->addItem(">90 Punkte");
    }


    QList< Database::Player* > playerlist = m_livegame->playersSortedByPosition->value();
    QListIterator< Database::Player* > it(playerlist);
    while (it.hasNext()){
        ui->comboBoxPlayer->addItem(it.next()->name->value());
    }

    setWindowModality(Qt::WindowModal);
}

SchmeissereiWidget::~SchmeissereiWidget()
{
    delete ui;
}

void SchmeissereiWidget::on_pushButton_clicked()
{
    Database::Round *r;
    Database::DokoRound* round;
    r = m_livegame->currentRound->value();
    Q_ASSERT(r != 0);
    round = static_cast<Database::DokoRound*>(r);
    Q_ASSERT(round != 0);

    round->addSchmeisserei(Database::Players::instance()->playerByName(ui->comboBoxPlayer->currentText()),ui->comboBoxType->currentText());
    emit schmeissereiAdded();
    this->reject();
}

void Gui::Details::LiveGameDetails::DokoLiveGameDetails::SchmeissereiWidget::on_pushButtonClose_clicked()
{
    this->reject();
}
