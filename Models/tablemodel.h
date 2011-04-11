#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

#include <Database/row.h>

#include <QStringList>
#include <QMimeData>

namespace Database {
    template<class T, class R>
    class Attribute;
}

namespace Models {

class TableModelBase : public QAbstractTableModel
{
public:
    TableModelBase(QObject *parent);

    virtual Database::Row *row(const QModelIndex &index) = 0;
};

template<class RowType, class Owner>
class TableModel : public TableModelBase
{
public:
    TableModel(Owner *parent);

    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    RowType *value(const QModelIndex &index);
    Database::Row *row(const QModelIndex &index);

private:
    void updateCache(::Database::Row *row);

    Database::Attribute<QHash<int, RowType*>, Owner> *m_data;
    Owner *m_owner;
};

template<class RowType, class Owner>
TableModel<RowType, Owner>::TableModel(Owner *parent) :
    TableModelBase(parent),
    m_data(parent->rows()),
    m_owner(parent)
{
    this->setSupportedDragActions(Qt::CopyAction);
}

template<class RowType, class Owner>
void TableModel<RowType, Owner>::updateCache(::Database::Row *row)
{
//    Database::Player *player = qobject_cast<Database::Player*>(row);
//    if(player != 0 && !m_players.contains(player))
//    {
//        beginInsertRows(QModelIndex(),m_players.size(),m_players.size());
//        m_players.append(player);
//        endInsertRows();
//    }
//    else
//    {
//        for(int i = 0; i < m_players.size(); i++)
//        {
//            QPointer<Database::Player> p = m_players.at(i);
//            if(p.isNull() || p == row)
//            {

//                beginRemoveRows(QModelIndex(),i,i);
//                m_players.removeAt(i);
//                endRemoveRows();
//                --i;

//            }
//        }
//    }
}

template<class RowType, class Owner>
QStringList TableModel<RowType, Owner>::mimeTypes() const
{
    QStringList types;
    RowType r;
    types << r.mimeType();
    return types;
}

template<class RowType, class Owner>
QMimeData *TableModel<RowType, Owner>::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    foreach (QModelIndex index, indexes)
    {
        if (index.isValid())
        {
            RowType* row = m_data->value().value(index.row(),0);
            stream << row->id();
        }
    }
    RowType r;
    mimeData->setData(r.mimeType(), encodedData);
    return mimeData;
}

template<class RowType, class Owner>
Qt::ItemFlags TableModel<RowType, Owner>::flags(const QModelIndex &index) const
{
    //1. Fall: index ist nicht valid
    if(!index.isValid())
    {
        return 0;
    }

    //sonst: default flags
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);
    return defaultFlags | Qt::ItemIsDragEnabled;
}

template<class RowType, class Owner>
int TableModel<RowType, Owner>::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return 0;
    }

    return m_data->value().size();
}

template<class RowType, class Owner>
int TableModel<RowType, Owner>::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return 0;
    }

    return m_owner->registeredAttributes()->size();
}

template<class RowType, class Owner>
QVariant TableModel<RowType, Owner>::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >=  m_data->value().size())
    {
        return QVariant();
    }

    RowType *row = m_data->value().values().at(index.row());
    if(row == 0)
    {
        return QVariant();
    }

    QString name = m_owner->registeredAttributes()->values().at(index.column())->name();
    Database::AttributeBase *attribute = row->attribute(name);

    if(attribute == 0)
    {
        return QVariant();
    }

    if(role == Qt::DisplayRole && attribute->role() == Qt::DisplayRole )
    {
        return attribute->toVariant();
    }
    if(role == Qt::DecorationRole &&  attribute->role() == Qt::DecorationRole)
    {
        return attribute->toVariant();
    }

    return QVariant();
}

template<class RowType, class Owner>
QVariant TableModel<RowType, Owner>::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
    {
        return QVariant();
    }

    Database::AttributeBase *attribute = m_owner->registeredAttributes()->values().at(section);

    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return attribute->displayName();
    }
//    QPixmap pixmap;
    if(role == Qt::DecorationRole && orientation == Qt::Horizontal){
        switch(section)
        {
//        case PositionChangeColumn:
//            pixmap.load(":/graphics/icons/general/playerstate/blackarrow");
//            pixmap.scaled(20,20);
//            return pixmap;
        }
    }

    return QVariant();
}

template<class RowType, class Owner>
RowType *TableModel<RowType, Owner>::value(const QModelIndex &index)
{
    return row(index);
}

template<class RowType, class Owner>
Database::Row *TableModel<RowType, Owner>::row(const QModelIndex &index)
{
    if(!index.isValid())
    {
        return 0;
    }
    int row = index.row();
    if(row >= m_data->value().size() || row < 0)
    {
        return 0;
    }

    return m_data->value().value(index.row(),0);
}

}

#endif // TABLEMODEL_H
