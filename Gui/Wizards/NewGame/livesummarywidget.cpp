#include "livesummarywidget.h"
#include "ui_livesummarywidget.h"

#include "dokolivegamegroupbox.h"

#include <Database/livegame.h>
#include <Database/player.h>
#include <Database/Doppelkopf/dokolivegame.h>

using namespace Gui::Wizards::NewGame;

LiveSummaryWidget::LiveSummaryWidget(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::LiveSummaryWidget)
{
    ui->setupUi(this);

    setTitle(tr("Summary"));
}

LiveSummaryWidget::~LiveSummaryWidget()
{
    delete ui;
}

//void LiveSummaryWidget::fillWidget(Database::LiveGame *livegame)
//{
//    if (livegame != 0){
//	ui->labelType->setText(livegame->type());

//	QList<QPointer<Database::Player> > playerlist = livegame->playersSortedByPosition();
//	QListIterator<QPointer<Database::Player> > it(playerlist);
//	while (it.hasNext()){
//	    ui->gridLayoutPlayers->addWidget(new QLabel(it.next()->name()),ui->gridLayoutPlayers->rowCount(),0);
//	}

//	if (livegame->type() == "Doppelkopf"){
//	    Database::Doppelkopf::DokoLiveGame* dokogame = static_cast<Database::Doppelkopf::DokoLiveGame*>(livegame);

//	    if (ui->verticalLayoutTypeSpecial->count() > 0){
//		for (int i = 0; i<ui->verticalLayoutTypeSpecial->count();i++){
//		    ui->verticalLayoutTypeSpecial->itemAt(i)->widget()->setVisible(false);
//		    ui->verticalLayoutTypeSpecial->removeWidget(ui->verticalLayout->itemAt(i)->widget());
//		}
//	    }

//	    DokoLiveGameGroupBox* dokobox = new DokoLiveGameGroupBox(dokogame);
//	    dokobox->setEnabled(false);
//	    ui->verticalLayoutTypeSpecial->addWidget(dokobox);
//	}
//    }
//}

