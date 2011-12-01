#include "offlinegameresultwidget.h"
#include "ui_offlinegameresultwidget.h"

#include "newgamewizard.h"

#include <Misc/handler.h>
#include <Database/player.h>
#include <Database/game.h>
#include <Gui/Misc/placescombobox.h>

#include <QSpinBox>
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>

using namespace Gui::Wizards::NewGame;

OfflineGameResultWidget::OfflineGameResultWidget(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::OfflineGameResultWidget)
{
    ui->setupUi(this);

    setupWidget();

    registerField("comment",ui->textEditComment, "plainText");
    registerField("date",ui->dateEdit);
    registerField("place",m_placesComboBox, "currentText");
    registerField("type",ui->comboBoxType ,"currentText");
    registerField("name",ui->lineEditName ,"currentText");

    connect(ui->lineEditName,SIGNAL(textChanged(QString)),this,SIGNAL(completeChanged()));
    connect(ui->comboBoxResidence, SIGNAL(currentIndexChanged(int)),this,SIGNAL(completeChanged()));
    connect(m_placesComboBox,SIGNAL(currentIndexChanged(int)),this,SIGNAL(completeChanged()));

    this->setTitle(tr("Offline game details"));
}

OfflineGameResultWidget::~OfflineGameResultWidget()
{
    delete ui;
}

void OfflineGameResultWidget::setupWidget()
{
    QList<QString> typelist = Database::Games::instance()->possibleTypes();

    QListIterator<QString> it(typelist);
    while (it.hasNext())
    {
        ui->comboBoxType->addItem(it.next());
    }

    m_placesComboBox = new Gui::Misc::PlacesComboBox(this);
    ui->gridLayout->addWidget(m_placesComboBox,3,2);

    connect(ui->calendarWidgetDate,SIGNAL(clicked(QDate)),ui->dateEdit,SLOT(setDate(QDate)));
    connect(ui->dateEdit,SIGNAL(dateTimeChanged(QDateTime)),ui->calendarWidgetDate,SLOT(setSelectedDate(QDate)));
    ui->dateEdit->setDateTime(QDateTime().currentDateTime());
}

int OfflineGameResultWidget::nextId() const
{
    return NewGameWizard::Page_OfflineSummary;
}

void OfflineGameResultWidget::initializePage()
{
    for(int i = this->field("OfflineGame_PlayerNumber").toInt(); i < ui->gridLayoutPositions->rowCount(); i++)
    {
        if (ui->gridLayoutPositions->itemAtPosition(i,0) != 0)
        {
            ui->gridLayoutPositions->itemAtPosition(i,0)->widget()->setVisible(false);
            ui->gridLayoutPositions->removeWidget(ui->gridLayoutPositions->itemAtPosition(i,0)->widget());
        }
        if (ui->gridLayoutPositions->itemAtPosition(i,1) != 0)
        {
            ui->gridLayoutPositions->itemAtPosition(i,1)->widget()->setVisible(false);
            ui->gridLayoutPositions->removeWidget(ui->gridLayoutPositions->itemAtPosition(i,1)->widget());
        }
    }

    for (int i = ui->gridLayoutPositions->rowCount() - 1; i < this->field("OfflineGame_PlayerNumber").toInt(); i++)
    {
        QLabel* ranking = new QLabel(QString("%1.").arg(i+1));
        ui->gridLayoutPositions->addWidget(ranking,i,0);

        QComboBox* comboBox = new QComboBox(this);

        foreach(Database::Player *player, Database::Players::instance()->allRows())
        {
            comboBox->addItem(player->name->value());
        }
        ui->gridLayoutPositions->addWidget(comboBox,i,1);
        connect(comboBox,SIGNAL(currentIndexChanged(int)),this,SIGNAL(completeChanged()));
        registerField("player"+QString::number(i+1),comboBox,"currentText");

        ui->gridLayoutPositions->setColumnStretch(i,1);
    }
}

bool OfflineGameResultWidget::isComplete() const
{
    if (ui->lineEditName->text() == "")
    {
	return false;
    }
    if (m_placesComboBox->currentText() == tr("Create new place...") )
    {
	return false;
    }
    for (int i = 0; i<ui->gridLayoutPositions->rowCount();i++)
    {
        for (int j = 0; j<ui->gridLayoutPositions->rowCount();j++)
        {
            if (i != j)
            {
                if (ui->gridLayoutPositions->itemAtPosition(i,1) != 0 && ui->gridLayoutPositions->itemAtPosition(j,1) != 0)
                {
		    if (static_cast<QComboBox*>(ui->gridLayoutPositions->itemAtPosition(i,1)->widget())->currentText()
			== static_cast<QComboBox*>(ui->gridLayoutPositions->itemAtPosition(j,1)->widget())->currentText())
                    {
			return false;
		    }
		}
	    }
	}
    }

    return true;
}
