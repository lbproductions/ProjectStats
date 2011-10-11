#ifndef PLAYERRESIDENCEWIDGET_H
#define PLAYERRESIDENCEWIDGET_H

#include <QWidget>

class QComboBox;

namespace Database{
class Place;
class Player;
class PlayerPlaceAssignment;
}

namespace Gui
{

namespace Misc
{
class PlacesComboBox;
}

namespace Details
{

class PlayerResidenceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerResidenceWidget(Database::Player* player, QWidget *parent = 0);
    PlayerResidenceWidget(Database::Player* player, Database::Place* place, QWidget *parent = 0);

private:
    void setupWidget();

    Misc::PlacesComboBox* m_comboBox;

    Database::Player* m_player;
    Database::Place* m_place;
    Database::PlayerPlaceAssignment* m_assignment;



signals:
    void newPlaceRequested();
    void placeAssignmentDeleted();


public slots:

    void onComboBoxCurrentPlaceChanged(Database::Place*const old, Database::Place*const current);
    void onPushButtonRemoveClicked();

};

}}

#endif // PLAYERRESIDENCEWIDGET_H
