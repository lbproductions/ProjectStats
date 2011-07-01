#include "sidebartreeview.h"

#include "../mainwindow.h"
#include "sidebar.h"
#include "sidebaritemdelegate.h"

#include <Database/Categories/childcategorie.h>
#include <Database/Categories/foldercategorie.h>
#include <Models/tablemodel.h>
#include <Models/categoriesmodel.h>
#include <Database/categorie.h>
#include <Database/database.h>
#include <handler.h>

#include <QHeaderView>
#include <QFont>
#include <QDragMoveEvent>
#include <QDebug>

using namespace Gui::MainWindow;

SidebarTreeView::SidebarTreeView(Sidebar *parent) :
    QTreeView(parent),
    m_model(0)
{
#ifdef Q_WS_MAC
    this->setDropIndicatorShown(true);
    this->setDragDropMode(QAbstractItemView::DropOnly);
    this->setAcceptDrops(true);
    this->setIconSize(QSize(32,32));
    setFrameStyle(QFrame::NoFrame);
    setAttribute(Qt::WA_MacShowFocusRect, false);
    setAutoFillBackground(true);
    setItemDelegate(new SidebarItemDelegate(this));

    // Set the palette.
    QPalette p = palette();
    QColor macSidebarColor(221, 228, 235);
    p.setColor(QPalette::Base, macSidebarColor);
    setPalette(p);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTextElideMode(Qt::ElideMiddle);
    setIndentation(10);


    setStyleSheet("QTreeView::branch:open:has-children:!has-siblings, "
                  "QTreeView::branch:open:has-children:has-siblings  {"
                         "border-image: none;"
                         "image: none /*url(:/graphics/styles/mac/sidebar/treeview-item-expanded-osx)*/;"
                  "}"
                  "QTreeView::branch:has-children:!has-siblings:closed,"
                  "QTreeView::branch:closed:has-children:has-siblings {"
                         "border-image: none;"
                         "image: none /*url(:/graphics/styles/mac/sidebar/treeview-item-closed-osx)*/;"
                  "}"
                  "QTreeView { "
                  "selection-background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, "
                  "stop:0 rgba(172, 188, 224, 255), "
                  "stop:1 rgba(126, 149, 187, 255))"
                    "}"
                  "QTreeView::item { "
                  "border-top: 1px solid #dde4eb;"
                "}"
                  "QTreeView::item:selected { "
                    "font-weight: bold;"
                    "border-top: 1px solid #a0afcd;"
                  "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, "
                  "stop:0 rgba(172, 188, 224, 255), "
                  "stop:1 rgba(126, 149, 187, 255))"
                  "}"
                    );

#endif

    setUniformRowHeights(false);
    header()->hide();

    setMinimumWidth(100);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    setAcceptDrops(true);
    setDropIndicatorShown(true);

    connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(on_clicked(QModelIndex)));

    //m_model = Handler::getInstance()->database()->categories()->categoriesModel();
    m_model = new Models::CategoriesModel(Database::Categories::instance());
    setModel(m_model);

    connect(m_model,SIGNAL(folderItemAdded(::Database::FolderCategorie*,QStandardItem*)),
	    this, SLOT(on_folderItemAdded(::Database::FolderCategorie*,QStandardItem*)));

    expandAll();

    selectionModel()->setCurrentIndex(
	    m_model->index(0,0,m_model->index(0,0,QModelIndex()))
	    ,QItemSelectionModel::Select);

    //connect(Handler::getInstance()->database()->categories(),SIGNAL(rowCreated(::Database::Row*)),this,SLOT(resetModel()));
}

void SidebarTreeView::on_folderItemAdded(::Database::FolderCategorie*,QStandardItem* item)
{
    selectionModel()->reset();
    selectionModel()->setCurrentIndex(item->index(),QItemSelectionModel::Select);
    this->edit(item->index());
}

void SidebarTreeView::on_clicked(const QModelIndex &index)
{
    if(index == m_currentIndex)
    {
	return;
    }

    m_currentIndex = index;
    Database::ChildCategorie *categorie = static_cast<Database::ChildCategorie *>(index.data(Qt::UserRole + 1).value<void*>());

    if(categorie == 0 || categorie->isParentCategorie())
    {
	return;
    }

    emit categorieChanged(categorie);
}

Database::ChildCategorie *SidebarTreeView::selectedCategorie() const
{
    if(selectedIndexes().isEmpty())
    {
	return 0;
    }
    return static_cast<Database::ChildCategorie *>(selectedIndexes().at(0).data(Qt::UserRole + 1).value<void*>());
}

void SidebarTreeView::dragMoveEvent(QDragMoveEvent *event)
{
    Database::FolderCategorie* c = static_cast<Database::FolderCategorie *>(indexAt(event->pos()).data(Qt::UserRole + 1).value<void*>());

    if(c == 0 || c->type->value() != Database::Categorie::FolderCategorieType)
    {
	event->ignore();
	return;
    }

    if(c->acceptMimeTypes(event->mimeData()->formats()))
    {
	event->acceptProposedAction();
	return;
    }

    event->ignore();
}

void SidebarTreeView::dropEvent(QDropEvent *event)
{
    Database::FolderCategorie* c = static_cast<Database::FolderCategorie *>(indexAt(event->pos()).data(Qt::UserRole + 1).value<void*>());

    if(c == 0 || c->type->value() != Database::Categorie::FolderCategorieType)
    {
	event->ignore();
	return;
    }

    if(c->acceptMimeTypes(event->mimeData()->formats()))
    {
	c->dropMimeData(event->mimeData());
	event->acceptProposedAction();
	return;
    }

    event->ignore();
}
