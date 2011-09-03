#ifndef PLAYERDETAILSWIDGET_H
#define PLAYERDETAILSWIDGET_H

#include <Gui/Details/detailswidget.h>

#include <QPointer>

namespace Ui {
    class PlayerWidget;
}

class QColorDialog;

namespace Database
{
    class Player;
    class Place;
}


namespace Gui
{

namespace Misc
{
    class ClickableLabel;
}

namespace Details
{

class PlayerResidenceWidget;

class PlayerDetailsWidget : public DetailsWidget
{
    Q_OBJECT

public:
    explicit PlayerDetailsWidget(Database::Player *player, QWidget *parent = 0);
    ~PlayerDetailsWidget();

    void setEditable(bool editable);

    void connectToAttributes();

private slots:
    void readPlayerData();
    void onPushButtonChooseColorClicked();
    void colorSelected(const QColor &color);
    void onLineEditNameEditingFinished();
    void onAvatarClicked();

    void onPlayerResidenceWidgetNewPlaceRequested();
    void onPlayerResidenceWidgetRemovePlaceRequested();

    void on_spinBoxWeight_valueChanged(int weight);

    void on_spinBoxSize_valueChanged(int size);

    void on_comboBoxGender_currentIndexChanged(QString gender);

private:
    Ui::PlayerWidget *ui;

    QPointer<Database::Player> m_player;
    QPointer<QColorDialog> m_colorDialog;
    QPointer<Misc::ClickableLabel> m_labelAvatar;
    QList<PlayerResidenceWidget*> m_playerResidenceWidgets;
    bool m_editable;
};

}

}

#endif // PLAYERDETAILSWIDGET_H
