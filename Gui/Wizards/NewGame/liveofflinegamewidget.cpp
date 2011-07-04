#include "liveofflinegamewidget.h"
#include "ui_liveofflinegamewidget.h"

#include "newgamewizard.h"

#include <QSettings>

using namespace Gui::Wizards::NewGame;

LiveOfflineGameWidget::LiveOfflineGameWidget(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::LiveOfflineGameWidget)
{
    ui->setupUi(this);

    QSettings settings;

    ui->radioButtonLiveGame->setChecked(settings.value("LiveOfflineGameWidget/radioButtonLiveGameChecked",true).toBool());
    ui->radioButtonOfflineGame->setChecked(!settings.value("LiveOfflineGameWidget/radioButtonLiveGameChecked",true).toBool());

    registerField("isLive",ui->radioButtonLiveGame);

    this->setTitle(tr("Choose Game-Type"));
    this->setSubTitle(tr("Please choose the type of the game, that you want to create:"));
}

LiveOfflineGameWidget::~LiveOfflineGameWidget()
{
    saveOptions();
    delete ui;
}

void LiveOfflineGameWidget::saveOptions() const
{
    QSettings settings;
    settings.setValue("LiveOfflineGameWidget/radioButtonLiveGameChecked",ui->radioButtonLiveGame->isChecked());
}

int LiveOfflineGameWidget::nextId() const
{
    saveOptions();

    if (ui->radioButtonLiveGame->isChecked())
    {
        return NewGameWizard::Page_LiveGameGeneralOptions;
    }
    if (ui->radioButtonOfflineGame->isChecked())
    {
        return NewGameWizard::Page_OfflineGameOptions;
    }

    return -1;
}
