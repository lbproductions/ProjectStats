#ifndef PLACEDETAILSWIDGET_H
#define PLACEDETAILSWIDGET_H

#include <QPointer>

#include <Gui/Details/detailswidget.h>

namespace Ui {
    class PlaceDetailsWidget;
}

namespace Database
{
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

class GoogleMap;

class PlaceDetailsWidget : public Gui::Details::DetailsWidget
{
    Q_OBJECT

public:
    explicit PlaceDetailsWidget(Database::Place* p, QWidget *parent = 0);
    ~PlaceDetailsWidget();

    void setEditable(bool editable);

    void readPlaceData();

private:
    Ui::PlaceDetailsWidget *ui;

    QPointer<Database::Place> m_place;

    QString m_filePath;
    QPointer<Misc::ClickableLabel> m_labelPicture;
    QPointer<GoogleMap> m_map;

private slots:
    void on_lineEditPLZ_editingFinished();
    void on_lineEditTown_editingFinished();
    void on_lineEditStreet_editingFinished();
    void on_lineEditNumber_editingFinished();
    void on_textEditComment_textChanged();
    void on_comboBoxPlayer_currentIndexChanged(QString name);
    void onlabelPicclicked();
    void on_pushButtonReload_clicked();
};

}
}


#endif // PLACEDETAILSWIDGET_H
