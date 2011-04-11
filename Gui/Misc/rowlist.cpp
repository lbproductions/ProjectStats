#include "rowlist.h"

#include <Models/tablemodel.h>

#include <QSortFilterProxyModel>
#include <QSettings>
#include <QList>
#include <QItemSelectionRange>

using namespace Gui::Misc;

RowList::RowList(Models::TableModelBase *model, QWidget *parent) :
    QTreeView(parent),
    m_proxyModel(0),
    m_model(0)
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

    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_doubleClicked(QModelIndex)));
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
