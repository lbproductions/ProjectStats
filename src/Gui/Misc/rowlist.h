#ifndef ROWLIST_H
#define ROWLIST_H

#include <QTreeView>
#include <QPointer>

class QSortFilterProxyModel;

namespace Models
{
    class TableModelBase;
}

namespace Database
{
    class Row;
    class AttributeBase;
}

namespace Gui
{

namespace Misc
{


//! Stellt eine Liste von Elementen (z.B. Spielen) dar.
/*!
  Diese Listen werden von TableModel bereitgstellt (siehe z.B. GamesModel).<br>
  Die Klasse ItemsList verwaltet anschließend das Auswählen und Klicks auf Listenelemente.
  */
class RowList : public QTreeView
{
    Q_OBJECT
public:
    /*!
      Erstellt eine ItemsList, die im MainWindow \p parent angezeigt wird. Der Konstruktor initialisiert diese Liste mit einem PlayersModel und gutem Aussehen für Mac OS X.
      */
    explicit RowList(Models::TableModelBase *model = 0, QWidget *parent = 0);

    /*!
      Speichert die aktuelle Größe der Liste.
      */
    ~RowList();

    /*!
      Setzt das Model der Liste auf \p model.
      */
    void setModel(Models::TableModelBase *model);

    Models::TableModelBase *model() const;

    Database::AttributeBase* attributeAt(const QPoint& point);

signals:
    /*!
      Dieses Signal wird gesendet, wenn ein Element doppelt geklickt wurde.
      */
    void rowDoubleClicked(Database::Row *row);
    /*!
      Dieses Signal wird gesendet, wenn mehrere Element der Liste angewählt wurden.
      */
    void rowsSelected(QList<Database::Row*> rows);

    /*!
      Dieses Signal wird gesendet, wenn sich die Auswahl der Liste allgemein geändert hat.
      */
    void selectionChanged();

protected slots:
    /*!
      Dieser Slot wird aktiviert, wenn sich die Auswahl allgemein geändert hat.<br>
      Dann werden die angewählten Elemente aus dem Model ausgelesen und korrekt gecastet (z.B. auf Game) von den jeweiligen Signals gesendet.
      */
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    /*!
      Dieser Slot wird aktiviert, wenn ein Element der Liste doppelt geklickt wird.
      Dann wird das angewählte Element aus dem Model ausgelesen und korrekt gecastet (z.B. auf Game) von den jeweiligen Signals gesendet.
      */
    void on_doubleClicked(QModelIndex);

    /*!
      Dieser Slot wird aktiviert, wenn sich die Liste der sichtbaren Spalten im Model geändert hat.
      */
    void setupVisibleColumns();

    void on_customContextMenuRequested(const QPoint &pos);

    void on_editAttributeActionTriggered();

private:
    QSortFilterProxyModel* m_proxyModel; //!< In diesem Proxymodel wird das eigentlich angezeigte Model gewrappt, und ist somit sortierbar.
    Models::TableModelBase* m_model; //!< Das Model, das wir eigentlich anzeigen.
};

}

}

#endif // ROWLIST_H
