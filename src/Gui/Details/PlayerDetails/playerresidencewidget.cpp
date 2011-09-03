#include "playerresidencewidget.h"

#include <Gui/Misc/placescombobox.h>

#include <Database/playerplaceassignment.h>
#include <Database/player.h>
#include <Database/place.h>

#include <QHBoxLayout>
#include <QPushButton>

using namespace Gui::Details;

PlayerResidenceWidget::PlayerResidenceWidget(Database::Player* player, QWidget *parent) :
    QWidget(parent),
    m_player(player),
    m_place(0),
    m_assignment(0)
{
    setupWidget();
}

PlayerResidenceWidget::PlayerResidenceWidget(Database::Player* player, Database::Place* place, QWidget *parent) :
    QWidget(parent),
    m_player(player),
    m_place(place)
{
    setupWidget();

    foreach(Database::PlayerPlaceAssignment* a, Database::PlayerPlaceAssignments::instance()->allRows()){
        if(a->playerId->value() == m_player->id() && a->placeId->value() == m_place->id()){
            m_assignment = a;
            return;
        }
    }

}

void PlayerResidenceWidget::setupWidget(){
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_comboBox = new Misc::PlacesComboBox(this);
    if(m_place != 0){
        m_comboBox->setCurrentPlace(m_place->id());
    }
    connect(m_comboBox,SIGNAL(currentIndexChanged(Database::Place*const,Database::Place*const)),
            this,SLOT(onComboBoxCurrentPlaceChanged(Database::Place*const,Database::Place*const)));
    layout->addWidget(m_comboBox);
    QPushButton* add = new QPushButton("+",this);
    connect(add,SIGNAL(clicked()),this,SIGNAL(newPlaceRequested()));
    layout->addWidget(add);
    QPushButton* remove = new QPushButton("-",this);
    connect(remove,SIGNAL(clicked()),this,SLOT(onPushButtonRemoveClicked()));
    layout->addWidget(remove);

    this->setLayout(layout);

}

void PlayerResidenceWidget::onComboBoxCurrentPlaceChanged(Database::Place*const old, Database::Place*const current){
    if(current != 0){
        if(m_assignment == 0){
            foreach(Database::PlayerPlaceAssignment* a, Database::PlayerPlaceAssignments::instance()->allRows()){
                if(a->playerId->value() == m_player->id() && a->placeId->value() == current->id()){
                    m_assignment = a;
                    return;
                }
            }
            Database::PlayerPlaceAssignment* a = new Database::PlayerPlaceAssignment();
            a->playerId->setValue(m_player->id());
            a->placeId->setValue(current->id());
            a->table()->insertRow(a);
            m_assignment = a;
        }
        else{
            foreach(Database::PlayerPlaceAssignment* a, Database::PlayerPlaceAssignments::instance()->allRows()){
                if(a->playerId->value() == m_player->id() && a->placeId->value() == current->id()){
                    qWarning() << "Place is already existing!";
                    m_comboBox->setCurrentPlace(old->id());
                    return;
                }
            }
            m_assignment->placeId->setValue(current->id());
            m_place = current;
        }
    }
}

void PlayerResidenceWidget::onPushButtonRemoveClicked(){
    if(m_assignment != 0){
        m_assignment->table()->deleteRow(m_assignment);
        emit placeAssignmentDeleted();
    }
}

