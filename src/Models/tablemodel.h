#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

#include <Database/row.h>
#include <Database/databaseattribute.h>

#include <QStringList>
#include <QMimeData>

namespace Database {
    template<class T, class R, class C>
    class Attribute;

    template<class T>
    class Table;

    class AttributeBase;
}

namespace Models {

class TableModelBase : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModelBase(QObject *parent);

    virtual Database::Row *row(const QModelIndex &index) = 0;

    virtual void updateData() = 0;

    void setDisplayRole(AttributeVariant::DisplayRole role);

    AttributeVariant::DisplayRole displayRole();

    void setVisibleColumns(QList<int> list);
    QList<int> visibleColumns();

    virtual Database::AttributeBase* attributeAt(const QModelIndex& index) const = 0;

protected:
    AttributeVariant::DisplayRole m_displayRole;
    QList<int> m_visibleColumns;

signals:
    void visibleHeadersChanged();

private slots:
    virtual void on_attribute_changed(::Database::AttributeBase *attribute) = 0;

};

template<class RowType, class Owner>
class TableModel : public TableModelBase
{
public:
    TableModel(Owner *parent);
    TableModel(QList<RowType*> data, Owner *parent);

    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool setData(QList<RowType*> list);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    RowType *value(const QModelIndex &index);
    Database::Row *row(const QModelIndex &index);
    void setVisibleColumns(QList<QString> list);
    int headerIndex(QString headerName);

    void updateData();

    Database::AttributeBase* attributeAt(const QModelIndex& index) const;

private:
    friend class Database::Table<RowType>;

    void on_attribute_changed(::Database::AttributeBase *attribute);

    QList<RowType*> m_data;
    Owner *m_owner;
};

template<class RowType, class Owner>
TableModel<RowType, Owner>::TableModel(QList<RowType*> data, Owner *parent) :
    TableModelBase(parent),
    m_data(data),
    m_owner(parent)
{
    this->setSupportedDragActions(Qt::CopyAction);

    foreach(Database::AttributeOwner *owner, parent->rows()->value())
    {
        foreach(Database::AttributeBase *attribute, owner->attributes())
        {
            connect(attribute,SIGNAL(changed(::Database::AttributeBase *)),
                    this,SLOT(on_attribute_changed(::Database::AttributeBase *)));
        }
    }
}

template<class RowType, class Owner>
TableModel<RowType, Owner>::TableModel(Owner *parent) :
    TableModelBase(parent),
    m_data(parent->rows()->value().values()),
    m_owner(parent)
{
    this->setSupportedDragActions(Qt::CopyAction);

    foreach(Database::AttributeOwner *owner, parent->rows()->value())
    {
        foreach(Database::AttributeBase *attribute, owner->attributes())
        {
            connect(attribute,SIGNAL(changed(::Database::AttributeBase *)),
                    this,SLOT(on_attribute_changed(::Database::AttributeBase *)));
        }
    }
}

template<class RowType, class Owner>
void TableModel<RowType, Owner>::updateData()
{
    m_data = m_owner->rows()->value().values();
}

template<class RowType, class Owner>
bool TableModel<RowType, Owner>::setData(QList<RowType*> list)
{
    m_data = list;
    this->reset();
    return true;
}

template<class RowType, class Owner>
void TableModel<RowType, Owner>::on_attribute_changed(::Database::AttributeBase *attribute)
{
    RowType *row = static_cast<RowType*>(attribute->owner());

    int i = m_data.indexOf(row);
    int j = m_owner->registeredAttributes()->values().indexOf(attribute);

    QModelIndex changedIndex = index(i,j,QModelIndex());
    emit dataChanged(changedIndex, changedIndex);
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
            RowType* row = m_data.value(index.row(),0);
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

    RowType *row = m_data.at(index.row());
    QString name = m_owner->registeredAttributes()->values().at(index.column())->name();
    if(row->attribute(name) != 0 && row->attribute(name)->isDatabaseAttribute())
    {
        defaultFlags |= Qt::ItemIsEditable;
    }

    return defaultFlags | Qt::ItemIsDragEnabled;
}

template<class RowType, class Owner>
int TableModel<RowType, Owner>::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return 0;
    }

    return m_data.size();
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
Database::AttributeBase* TableModel<RowType, Owner>::attributeAt(const QModelIndex& index) const
{
    RowType *row = m_data.at(index.row());
    if(row == 0)
    {
        return 0;
    }

    QString name = m_owner->registeredAttributes()->values().at(index.column())->name();
    return row->attribute(name);
}

template<class RowType, class Owner>
QVariant TableModel<RowType, Owner>::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >=  m_data.size())
    {
        return QVariant();
    }

    Database::AttributeBase *attribute = attributeAt(index);

    if(!attribute)
    {
        return QVariant();
    }

    attribute->startCalculationTask();
    attribute->setDisplayRole(m_displayRole);
    QVariant value = attribute->displayVariant();

    if( (role == Qt::DisplayRole && attribute->role() == Qt::DisplayRole) || role == Qt::EditRole)
    {
        return value;
    }
    if(role == Qt::DecorationRole &&  attribute->role() == Qt::DecorationRole)
    {
        return value;
    }

    return QVariant();
}

template<class RowType, class Owner>
bool TableModel<RowType, Owner>::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        RowType *row = m_data.at(index.row());
        QString name = m_owner->registeredAttributes()->values().at(index.column())->name();
        Database::AttributeBase *attribute = row->attribute(name);

        if(attribute->isDatabaseAttribute())
        {
            attribute->changeValue(value,true);
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

template<class RowType, class Owner>
QVariant TableModel<RowType, Owner>::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
    {
        return QVariant();
    }
    if(section >= 0){
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
    if(row >= m_data.size() || row < 0)
    {
        return 0;
    }

    return m_data.at(index.row());
}

template<class RowType, class Owner>
void TableModel<RowType, Owner>::setVisibleColumns(QList<QString> list){
    QList<int> visible;
    foreach(QString string, list){
        for(int i = 0; i<m_owner->registeredAttributes()->size();i++){
            if(string == this->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString()){
                visible.append(i);
            }
        }
    }
    TableModelBase::setVisibleColumns(visible);
}

template<class RowType, class Owner>
int TableModel<RowType, Owner>::headerIndex(QString headerName) {
    for(int i = 0; i<m_owner->registeredAttributes()->size();i++){
        if(headerName == this->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString()){
            return i;
        }
    }
}

}

#endif // TABLEMODEL_H
