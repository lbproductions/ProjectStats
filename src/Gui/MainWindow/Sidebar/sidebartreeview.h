#ifndef CATEGORIESTREEVIEW_H
#define CATEGORIESTREEVIEW_H

#include <QTreeView>

class QStandardItem;

namespace Database
{
    class ChildCategorie;
    class FolderCategorie;
}

namespace Models
{
    class CategoriesModel;
}

namespace Gui
{

namespace MainWindow
{

class Sidebar;
class MainWindow;

//! Stellt die Kategorien, der Datenbank in einer Seitenleiste dar.
/*!
  Alle Categorie-Objekte werden von Categories verwaltet und bieten Informationen über ihr Aussehen und Inhalt.<br>
  Die Sidebar stellt diese einfach nur schlicht dar und signalisiert jede Änderung der aktuellen Kategorie.
  */
class SidebarTreeView : public QTreeView
{
    Q_OBJECT
public:
    /*!
      Erstellt die Seitenleiste für das MainWindow \\pparent.
      */
    SidebarTreeView(Sidebar *parent = 0);

    Database::ChildCategorie *selectedCategorie() const;

    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

signals:
    /*!
      Dieses Signal wird gesendet, wenn eine neue Categorie ausgewählt wurde.
      */
    void categorieChanged(Database::ChildCategorie*);

private slots:
    /*!
      Dieser Slot wird aktiviert, wenn ein Element der Seitenleiste angeklickt wurde.<br>
      Dann wird dieses Element zu Categorie gecastet und diese Änderung mit categorieChanged() mitgeteilt.
      */
    void on_clicked(const QModelIndex&);

    void on_folderItemAdded(::Database::FolderCategorie* folder,QStandardItem* item);

private:
    QModelIndex m_currentIndex; //!< Verwaltet den aktuell ausgewählten Index.

    Models::CategoriesModel *m_model;
};

}
}

#endif // CATEGORIESTREEVIEW_H
