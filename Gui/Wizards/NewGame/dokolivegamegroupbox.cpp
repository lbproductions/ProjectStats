#include "dokolivegamegroupbox.h"
#include "ui_dokolivegamegroupbox.h"

#include <Database/Doppelkopf/dokolivegame.h>

using namespace Gui::Wizards::NewGame;

DokoLiveGameGroupBox::DokoLiveGameGroupBox(Database::DokoLiveGame* livegame, QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::DokoLiveGameGroupBox)
{
    ui->setupUi(this);

    Q_ASSERT(livegame != 0);

    ui->checkBoxHochzeit->setChecked(livegame->doko_mitHochzeit->value());
    ui->checkBoxSchmeisserei->setChecked(livegame->doko_mitSchmeisserei->value());
    ui->checkBoxSchweinerei->setChecked(livegame->doko_mitSchweinerei->value());
    ui->checkBoxSolo->setChecked(livegame->doko_mitSolo->value());
    ui->checkBoxTrumpfabgabe->setChecked(livegame->doko_mitTrumpfabgabe->value());

    setTitle(tr("Special rules"));
}

DokoLiveGameGroupBox::~DokoLiveGameGroupBox()
{
    delete ui;
}
