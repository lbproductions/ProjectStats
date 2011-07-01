#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "../view.h"

#include <QPointer>

namespace Database
{
    class ChildCategorie;
    class Row;
}

class QScrollArea;
class QAction;

namespace Gui
{

namespace Details
{
    //class DetailsWidget;
    //class RowWidget;
}

namespace Misc
{
    class Splitter;
    class RowList;
}

namespace MainWindow
{
namespace Views
{

class ListView : public View
{
    Q_OBJECT
public:
    explicit ListView(Database::ChildCategorie* categorie, MainWindow *parent = 0);

    ~ListView();

public slots:
    void updateStatusbar();

private slots:
    /*!
      Dieser Slot wird aufgerufen, wenn sich in der ItemsList die Auswahl geändert hat.<br>
      Nach dieser sehr allgemeinen Info wird das DetailsWidget invisible gesetzt, was flackern verhindert, beim setzen des nächsten Widgets.
      */
    void on_rowList_selectionChanged();

    /*!
      Dieser Slot wird aufgerufen, wenn in der ItemsList ein Spiel ausgewählt wurde.<br>
      Dann wird das zum Spiel passende Widget als DetailsWidget gesetzt.
      */
    void on_rowList_rowsSelected(QList<Database::Row*>);

    /*!
      Dieser Slot wird aufgerufen, wenn ein Spiel in der ItemsList doppelt geklickt wurde.<br>
      Dann wird ein neues zum Spiel passendes Fenster geöffnet (z.B. ein LiveGameWidget)
      */
    void on_rowList_rowDoubleClicked(Database::Row*);

    void on_editActionToggled(bool checked);

private:
    void saveSettings();
    void restoreSettings();

    QAction *editButtonAction();

    QPointer<Database::ChildCategorie> m_categorie;

    QPointer<QScrollArea> m_scrollAreaDetails; //!< In dieser ScrollArea werden die DetailsWidgets angezeigt.
    //QPointer<Details::RowWidget> m_rowWidget; //!< Speichert das aktuelle RowWidget
    QPointer<Misc::Splitter> m_horizontalSplitter; //!< Enthält oben die ItemsList und unten ein DetailsWidget.
    QPointer<Misc::RowList> m_rowList;

    QPointer<QAction> m_editButtonAction;
};

}
}
}

#endif // LISTVIEW_H
