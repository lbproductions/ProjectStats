#include "offlinegameoptionswidget.h"
#include "ui_offlinegameoptionswidget.h"

#include <QLabel>
#include <QSettings>

#include "newgamewizard.h"

using namespace Gui::Wizards::NewGame;

OfflineGameOptionsWidget::OfflineGameOptionsWidget(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::OfflineGameOptionsWidget)
{
    ui->setupUi(this);

    QSettings settings;

    ui->checkBoxDetailled->setChecked(settings.value("OfflineGameOptionsWidget/checkBoxDetailledChecked",true).toBool());
    ui->comboBoxType->setEnabled(settings.value("OfflineGameOptionsWidget/checkBoxDetailledChecked",true).toBool());

    ui->comboBoxType->addItem("Doppelkopf");
    ui->comboBoxType->setCurrentIndex(settings.value("OfflineGameOptionsWidget/comboBoxTypeCurrentIndex",0).toInt());

    ui->spinBoxPlayerNumber->setValue(settings.value("OfflineGameOptionsWidget/spinBoxPlayerNumberValue",4).toInt());

    this->registerField("offlineGame_isDetailled",ui->checkBoxDetailled);
    this->registerField("type",ui->comboBoxType);
    this->registerField("playerCount",ui->spinBoxPlayerNumber);

    connect(ui->checkBoxDetailled,SIGNAL(stateChanged(int)),this, SIGNAL(completeChanged()));
    connect(ui->comboBoxType,SIGNAL(currentIndexChanged(int)),this, SIGNAL(completeChanged()));
    connect(ui->spinBoxPlayerNumber,SIGNAL(valueChanged(int)),this,SIGNAL(completeChanged()));

    this->setTitle(tr("Offline Game Options"));
    this->setSubTitle(tr("Refine the options for this game:"));
}

OfflineGameOptionsWidget::~OfflineGameOptionsWidget()
{
    saveOptions();
    delete ui;
}

void OfflineGameOptionsWidget::saveOptions() const
{
    QSettings settings;
    settings.setValue("OfflineGameOptionsWidget/checkBoxDetailledChecked",ui->checkBoxDetailled->isChecked());
    settings.setValue("OfflineGameOptionsWidget/comboBoxTypeCurrentIndex",ui->comboBoxType->currentIndex());
    settings.setValue("OfflineGameOptionsWidget/spinBoxPlayerNumberValue",ui->spinBoxPlayerNumber->value());
}

int OfflineGameOptionsWidget::nextId() const
{
    saveOptions();

    if(!ui->checkBoxDetailled->isChecked())
    {
        return NewGameWizard::Page_OfflineGameResult;
    }
    else
    {
        return NewGameWizard::Page_DetailledOfflineDokoGame;
    }

    return -1;
}

bool OfflineGameOptionsWidget::isComplete() const
{
    if(ui->checkBoxDetailled->isChecked())
    {
        if(ui->comboBoxType->currentText() == "Doppelkopf")
        {
            if(ui->spinBoxPlayerNumber->value() < 4)
            {
                return false;
            }
        }
    }

    if(ui->spinBoxPlayerNumber->value() <= 0)
    {
        return false;
    }

    return true;
}

void OfflineGameOptionsWidget::on_checkBoxDetailled_stateChanged()
{
    ui->comboBoxType->setEnabled(ui->checkBoxDetailled->isChecked());
}
