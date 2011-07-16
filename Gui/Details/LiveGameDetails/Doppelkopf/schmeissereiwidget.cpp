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
    ui(new Ui::SchmeissereiWidget),
    m_livegame(livegame)
{
    ui->setupUi(this);

    QFile newround(":/stylesheets/livegame/newroundwidget_fullscreen");
    newround.open(QFile::ReadOnly);
    setStyleSheet(newround.readAll());
    newround.close();

    if (m_livegame->doko_mitFuenfKoenige->value())
    {
        ui->comboBoxType->addItem(QString::fromUtf8("5 Könige"));
    }
    if (m_livegame->doko_mitZuWenigTrumpf->value())
    {
        ui->comboBoxType->addItem("Zu wenig Trumpf");
    }
    if (m_livegame->doko_mitTrumpfabgabeSchmeisserei->value())
    {
        ui->comboBoxType->addItem("Trumpfabgabe nicht genommen");
    }
    if (m_livegame->doko_mitNeunzigPunkte->value())
    {
        ui->comboBoxType->addItem(">90 Punkte");
    }

    foreach(Database::Player* player, m_livegame->playersSortedByPosition->value())
    {
        ui->comboBoxPlayer->addItem(player->name->value());
    }

    setWindowModality(Qt::WindowModal);
}

SchmeissereiWidget::~SchmeissereiWidget()
{
    delete ui;
}

void SchmeissereiWidget::on_pushButton_clicked()
{
    Database::DokoRound* round = static_cast<Database::DokoRound*>(m_livegame->currentRound->value());

    round->addSchmeisserei(Database::Players::instance()->playerByName(ui->comboBoxPlayer->currentText()),ui->comboBoxType->currentText());
    accept();
}

void SchmeissereiWidget::on_pushButtonClose_clicked()
{
    reject();
}
