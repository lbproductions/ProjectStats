#ifndef DRINKDETAILSWIDGET_H
#define DRINKDETAILSWIDGET_H

#include <QDialog>
#include <QPointer>

#include <Database/drink.h>
#include <Gui/Details/detailswidget.h>

namespace Ui {
    class DrinkDetailsWidget;
}

namespace Gui
{

namespace Misc
{
    class ClickableLabel;
}

namespace Details
{


class DrinkDetailsWidget : public Gui::Details::DetailsWidget
{
    Q_OBJECT

public:
    explicit DrinkDetailsWidget(Database::Drink* drink, QWidget *parent = 0);
    ~DrinkDetailsWidget();

    void setEditable(bool editable);

private slots:

    void onlabelPicclicked();

    void on_lineEditName_editingFinished();

    void on_comboBoxType_currentIndexChanged(QString );

    void on_doubleSpinBoxSize_editingFinished();

    void on_doubleSpinBoxAlc_editingFinished();

private:

    void readData();

    Ui::DrinkDetailsWidget *ui;

    QString m_filePath;
    QPointer<Misc::ClickableLabel> m_labelPicture;

    QPointer<Database::Drink> m_drink;
};

}
}

#endif // DRINKDETAILSWIDGET_H
