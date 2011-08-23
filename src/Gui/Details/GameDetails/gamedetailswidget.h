#ifndef OFFLINEGAMEDETAILSWIDGET_H
#define OFFLINEGAMEDETAILSWIDGET_H

#include <Gui/Details/detailswidget.h>

#include <QPointer>

namespace Ui {
    class GameWidget;
}

namespace Database
{
    class Game;
    class Place;
}

namespace Gui
{

    namespace Misc
    {
        class PlacesComboBox;
    }

    namespace Details
    {

        /**
        * Widget zur Darstellung von OfflineGames
        */
        class GameDetailsWidget : public DetailsWidget
        {
            Q_OBJECT

            public:
                /**
                * Erstellt ein neues GameWidget für das übergebene Game. Dabei werden die Positionen der Player in den GeneralTab eingetragen.
                */
                explicit GameDetailsWidget(Database::Game* game, QWidget *parent = 0);
                ~GameDetailsWidget();

                void setEditable(bool editable);

            private:
                Ui::GameWidget *ui;
                QPointer<Database::Game> m_game;
                QPointer<Misc::PlacesComboBox> m_placesComboBox;

                /**
                * Liest die Daten des Games aus.
                */
                void readData();

                void connectToAttributes();

            private slots:
                /**
                * Wird ausgeführt, wenn sich die ComboBox der Residence ändert
                */
                void onPlacesComboBoxCurrentIndexChanged(Database::Place *const oldPlace , Database::Place *const newPlace);
                /**
                * Wird ausgeführt, wenn sich der Text aus dem Comment-TextEdit geändert hat
                */
                void on_textEditComment_textChanged();
                /**
                * Wird ausgeführt, wenn sich der Text aus dem Name-LineEdit geändert hat
                */
                void on_lineEditName_editingFinished();

        };

    }

}

#endif // OFFLINEGAMEDETAILSWIDGET_H
