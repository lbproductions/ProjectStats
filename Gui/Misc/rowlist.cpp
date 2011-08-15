#include "rowlist.h"

#include "rowlistheader.h"

#include <Models/tablemodel.h>

#include <QSortFilterProxyModel>
#include <QSettings>
#include <QList>
#include <QItemSelectionRange>

using namespace Gui::Misc;

RowList::RowList(Models::TableModelBase *model, QWidget *parent) :
    QTreeView(parent),
    m_proxyModel(0),
    m_model(model)
{
#ifdef Q_WS_MAC
    setRootIsDecorated(false);
    setAlternatingRowColors(true);
    setFont(QFont("Lucida Grande",12));
    setFrameStyle(QFrame::NoFrame);
    setAttribute(Qt::WA_MacShowFocusRect, false);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setSelectionMode(QAbstractItemView::SingleSelection);
#endif

    setUniformRowHeights(true);
    setSortingEnabled(true);

    setModel(model);

    connect(m_model,SIGNAL(visibleHeadersChanged()),this,SLOT(setupVisibleColumns()));
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_doubleClicked(QModelIndex)));

    setHeader(new RowListHeader(Qt::Horizontal));
}

RowList::~RowList()
{
}

void RowList::setModel(Models::TableModelBase *model)
{
    if(m_proxyModel.isNull())
    {
	m_proxyModel = new QSortFilterProxyModel(this);
	QTreeView::setModel(m_proxyModel);
    }
    m_proxyModel->setSourceModel(model);
    m_model = model;
}

Models::TableModelBase *RowList::model() const
{
    return m_model;
}

void RowList::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QTreeView::selectionChanged(selected,deselected);
    emit selectionChanged();
    Q_ASSERT(m_model != 0);

    QItemSelection selectionInSource = m_proxyModel->mapSelectionToSource(selected);

    QList<Database::Row*> list;
    foreach(QModelIndex index, selectionInSource.indexes())
    {
        Database::Row *selectedRow = m_model->row(index);
	if(selectedRow != 0)
	{
	    list.append(selectedRow);
	}
    }
    emit rowsSelected(list);
}

void RowList::on_doubleClicked(QModelIndex index)
{
    Q_ASSERT(m_model != 0);

    QModelIndex indexInSource = m_proxyModel->mapToSource(index);

    Database::Row *selectedRow = m_model->row(indexInSource);
    if(selectedRow != 0)
    {
	emit rowDoubleClicked(selectedRow);
    }
}

void RowList::setupVisibleColumns()
{
    for(int i = 0; i<this->header()->count();i++){
        if(m_model->visibleColumns().contains(i)){
            this->setColumnHidden(i,false);
        }
        else{
            this->setColumnHidden(i,true);
        }
    }
    this->repaint();
}
