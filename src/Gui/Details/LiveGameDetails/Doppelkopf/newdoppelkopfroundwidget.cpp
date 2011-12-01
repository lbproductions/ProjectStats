#include "newdoppelkopfroundwidget.h"

#include <QGridLayout>

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>

#include <Gui/Misc/groupbox.h>
#include <Gui/Misc/playercheckbox.h>

#include <Gui/Details/LiveGameDetails/Doppelkopf/NewDokoRoundWidget/recolumn.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/NewDokoRoundWidget/hochzeitcolumn.h>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

NewDoppelkopfRoundWidget::NewDoppelkopfRoundWidget(Database::DokoLiveGame* game, QWidget *parent) :
    QDialog(parent),
    m_dokoLiveGame(game),
    m_soloType(""),
    m_reCount(0),
    m_re1Player(0),
    m_re2Player(0),
    m_hochzeitPlayer(0),
    m_trumpfabgabePlayer(0),
    m_schweinereiPlayer(0),
    m_soloPlayer(0)
{
    QPalette p(this->palette());
    p.setColor(QPalette::Background, QColor(55,55,55));
    this->setPalette(p);

    this->setStyleSheet("QLabel{color:white;}");

    setWindowModality(Qt::WindowModal);

    setupWidget();
}

NewDoppelkopfRoundWidget::~NewDoppelkopfRoundWidget()
{
}

void NewDoppelkopfRoundWidget::setupWidget(){
    this->setLayout(new QVBoxLayout(this));

    QGridLayout* layout = new QGridLayout(this);
    Misc::GroupBox* groupBox = new Misc::GroupBox(layout,this);
    this->layout()->addWidget(groupBox);

    // Names
    layout->addWidget(new QLabel(tr("Name"),this),0,0);
    int row = 1;
    foreach(Database::Player* player, m_dokoLiveGame->currentRound->value()->currentPlayingPlayers->value()){
        layout->addWidget(new QLabel(player->name->value(),this),row,0);
        row++;
    }


    // Re
    layout->addWidget(new QLabel(tr("Re"),this),0,1);
    ReColumn* reColumn = new ReColumn(m_dokoLiveGame,layout,1,1,this);


    //Hochzeit
    if(m_dokoLiveGame->doko_mitHochzeit->value()){
        layout->addWidget(new QLabel(tr("Hochzeit"),this),0,2);
        HochzeitColumn* hochzeitColumn = new HochzeitColumn(m_dokoLiveGame,layout,1,2,this);
        connect(hochzeitColumn,SIGNAL(hochzeitPlayerChanged(Database::Player*,bool)),
                reColumn,SLOT(onHochzeitPlayerChanged(Database::Player*,bool)));
        connect(reColumn,SIGNAL(rePlayersChanged(QMap<Database::Player*,bool>,int)),
                hochzeitColumn,SLOT(onRePlayersChanged(QMap<Database::Player*,bool>,int)));
    }
    /*
    if(m_dokoLiveGame->doko_mitHochzeit->value()){
        layout->addWidget(new QLabel(tr("Hochzeit"),this),0,2);
        int row = 1;
        foreach(Database::Player* player, m_dokoLiveGame->currentRound->value()->currentPlayingPlayers->value()){
            Misc::PlayerCheckBox* check = new Misc::PlayerCheckBox(player,this);
            layout->addWidget(check,row,2);
            m_hochzeitBoxes.append(check);
            connect(check,SIGNAL(checkStateChanged(Misc::CheckBox*,bool)),this,SLOT(hochzeitPlayerChanged(Misc::CheckBox*,bool)));
            row++;
        }
    }
    */
    //Trumpfabgabe
    if(m_dokoLiveGame->doko_mitTrumpfabgabe->value()){
        layout->addWidget(new QLabel(tr("Trumpfabgabe"),this),0,3);
    }

    //Schweinerei
    if(m_dokoLiveGame->doko_mitSchweinerei->value()){
        layout->addWidget(new QLabel(tr("Schweinerei"),this),0,4);
    }

    //Solo
    if(m_dokoLiveGame->doko_mitSolo->value()){
        layout->addWidget(new QLabel(tr("Solo"),this),0,5);

        createSoloCheckBox();
    }

}

void NewDoppelkopfRoundWidget::createSoloCheckBox(){
    QHBoxLayout* soloLayout = new QHBoxLayout(this);
    if(m_dokoLiveGame->doko_mitBubensolo->value()){
        Misc::CheckBox* checkBox = new Misc::CheckBox(tr("Buben"),this);
        connect(checkBox,SIGNAL(checkStateChanged(Misc::CheckBox*,bool)),this,SLOT(soloTypeChanged(Misc::CheckBox*,bool)));
        m_soloCheckBoxes.append(checkBox);
        soloLayout->addWidget(checkBox);
    }
    if(m_dokoLiveGame->doko_mitDamensolo->value()){
        Misc::CheckBox* checkBox = new Misc::CheckBox(tr("Damen"),this);
        connect(checkBox,SIGNAL(checkStateChanged(Misc::CheckBox*,bool)),this,SLOT(soloTypeChanged(Misc::CheckBox*,bool)));
        m_soloCheckBoxes.append(checkBox);
        soloLayout->addWidget(checkBox);
    }
    if(m_dokoLiveGame->doko_mitTrumpfsolo->value()){
        Misc::CheckBox* checkBox = new Misc::CheckBox(tr("Trumpf"),this);
        connect(checkBox,SIGNAL(checkStateChanged(Misc::CheckBox*,bool)),this,SLOT(soloTypeChanged(Misc::CheckBox*,bool)));
        m_soloCheckBoxes.append(checkBox);
        soloLayout->addWidget(checkBox);
    }
    if(m_dokoLiveGame->doko_mitFarbsolo->value()){
        Misc::CheckBox* checkBox = new Misc::CheckBox(tr("Farben"),this);
        connect(checkBox,SIGNAL(checkStateChanged(Misc::CheckBox*,bool)),this,SLOT(soloTypeChanged(Misc::CheckBox*,bool)));
        m_soloCheckBoxes.append(checkBox);
        soloLayout->addWidget(checkBox);
    }
    if(m_dokoLiveGame->doko_mitFleischlos->value()){
        Misc::CheckBox* checkBox = new Misc::CheckBox(tr("Fleischlos"),this);
        connect(checkBox,SIGNAL(checkStateChanged(Misc::CheckBox*,bool)),this,SLOT(soloTypeChanged(Misc::CheckBox*,bool)));
        m_soloCheckBoxes.append(checkBox);
        soloLayout->addWidget(checkBox);
    }
    if(m_dokoLiveGame->doko_mitSchwarzsolo->value()){
        Misc::CheckBox* checkBox = new Misc::CheckBox(tr("Schwarz"),this);
        connect(checkBox,SIGNAL(checkStateChanged(Misc::CheckBox*,bool)),this,SLOT(soloTypeChanged(Misc::CheckBox*,bool)));
        m_soloCheckBoxes.append(checkBox);
        soloLayout->addWidget(checkBox);
    }
    m_soloGroupBox = new Misc::GroupBox(soloLayout,this);
    m_soloGroupBox->setVisible(false);
    this->layout()->addWidget(m_soloGroupBox);
}

void NewDoppelkopfRoundWidget::soloTypeChanged(Misc::CheckBox* check,bool checked){
    if(checked){
        m_soloType = check->text();
    }
    else{
        m_soloType = "";
    }
}

void NewDoppelkopfRoundWidget::rePlayersChanged(Misc::CheckBox* check, bool checked){
    qDebug() << "checked: " << checked;
    if(checked){
        Misc::PlayerCheckBox* playerBox = static_cast<Misc::PlayerCheckBox*>(check);
        m_reCount++;
        if(m_reCount == 1){
            m_re1Player = playerBox->player();
            m_re2Player = 0;
            if(m_hochzeitPlayer != 0){
                foreach(Misc::PlayerCheckBox* checkBox, m_hochzeitBoxes){
                    if(checkBox->player() != m_hochzeitPlayer){
                        checkBox->setEnabled(false);
                    }
                }
             }
        }
        else if(m_reCount == 2){
            m_re2Player = playerBox->player();
            foreach(Misc::PlayerCheckBox* checkBox, m_reCheckBoxes){
                if(!checkBox->isChecked()){
                    checkBox->setEnabled(false);
                }
            }
            if(m_hochzeitPlayer == 0){
                foreach(Misc::PlayerCheckBox* checkBox, m_hochzeitBoxes){
                    if(checkBox->player() != m_re1Player && checkBox->player() != m_re2Player){
                        checkBox->setEnabled(false);
                    }
                    else{
                        checkBox->setEnabled(true);
                    }
                }
             }
            else{
                foreach(Misc::PlayerCheckBox* checkBox, m_hochzeitBoxes){
                    if(checkBox->player() != m_hochzeitPlayer){
                        checkBox->setEnabled(false);
                    }
                }
            }
        }
    }
    else{
        m_reCount--;
        foreach(Misc::PlayerCheckBox* checkBox, m_reCheckBoxes){
            if(checkBox->player() != m_re1Player){
                checkBox->setEnabled(true);
            }
        }
        if(m_reCount == 1){
            if(m_hochzeitPlayer == 0){
                foreach(Misc::PlayerCheckBox* checkBox, m_hochzeitBoxes){
                    checkBox->setEnabled(true);
                }
             }

        }
        else{
            m_re1Player = 0;
            m_re2Player = 0;
        }
    }
}

void NewDoppelkopfRoundWidget::hochzeitPlayerChanged(Misc::CheckBox* check, bool checked){
    if(checked){
        Misc::PlayerCheckBox* playerBox = static_cast<Misc::PlayerCheckBox*>(check);
        m_hochzeitPlayer = playerBox->player();
        foreach(Misc::PlayerCheckBox* checkBox, m_hochzeitBoxes){
            if(!checkBox->isChecked()){
                checkBox->setEnabled(false);
            }
        }
        foreach(Misc::PlayerCheckBox* checkBox, m_reCheckBoxes){
            if(checkBox->player() == m_hochzeitPlayer){
                checkBox->setChecked(true);
                checkBox->setEnabled(false);
            }
        }

    }
    else{
        m_hochzeitPlayer = 0;
        if(m_reCount == 2){
            foreach(Misc::PlayerCheckBox* checkBox, m_hochzeitBoxes){
                if(checkBox->player() != m_re1Player && checkBox->player() != m_re2Player){
                    checkBox->setEnabled(false);
                 }
                 else{
                    checkBox->setEnabled(true);
                }
            }
            foreach(Misc::PlayerCheckBox* checkBox, m_reCheckBoxes){
                if(checkBox->player() != m_re1Player && checkBox->player() != m_re2Player){
                    checkBox->setEnabled(false);
                 }
                 else{
                    checkBox->setEnabled(true);
                }
            }
        }
        else{
            foreach(Misc::PlayerCheckBox* checkBox, m_hochzeitBoxes){
                checkBox->setEnabled(true);
            }
            foreach(Misc::PlayerCheckBox* checkBox, m_reCheckBoxes){
                checkBox->setEnabled(true);
            }
        }
    }
}
