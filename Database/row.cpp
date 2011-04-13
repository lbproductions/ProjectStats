#include "row.h"

#include "attribute.h"
#include "table.h"

namespace Database {

Row::Row(int id, TableBase *table) :
    AttributeOwner(table),
    m_id(id),
    m_table(table),
    m_attributes(QHash<QString, AttributeBase* >())
{
}

void Row::checkId()
{
    if(!get("id").isValid()) {
        m_id = 0;
    }
}

int Row::id() const
{
    return m_id;
}

void Row::setId(int id)
{
    m_id = id;
}

QSqlQuery Row::query(const QString &queryString) const
{
    return m_table->query(queryString);
}

bool Row::set(const QString &key, const QVariant &value)
{
    return set(key,value,"id = "+QString::number(m_id));
}


bool Row::set(const QString &key, const QVariant &value, const QString &condition)
{
    if(m_id != 0)
    {
        QSqlQuery q = query("UPDATE "+m_table->name()+" SET "+key+" = '"+value.toString()+"' WHERE "+condition+";");
        q.finish();
        return q.isValid();
    }

    return false;
}

QVariant Row::get(const QString &key) const
{
    QVariant value = get(key, "id = "+QString::number(m_id));
    return value;
}

QList<AttributeBase*> Row::attributes() const
{
    return m_attributes.values();
}

QList<AttributeBase*> Row::databaseAttributes() const
{
    return m_databaseAttributes;
}

AttributeBase *Row::attribute(const QString &name) const
{
    return m_attributes.value(name);
}

void Row::registerAttribute(AttributeBase *attribute)
{
    m_attributes.insert(attribute->name(), attribute);

    if(attribute->isDatabaseAttribute())
    {
        m_databaseAttributes.append(attribute);
    }
}

QVariant Row::get(const QString &key, const QString &condition) const
{
    QSqlQuery select = query("SELECT "+key+" FROM "+m_table->name()+" WHERE "+condition+";");

    select.first();
    if(select.isValid())
    {
        QVariant result = select.value(0);
        select.finish();
        return result;
    }
    else
    {
        select.finish();
        return QVariant();
    }
}

void Row::deleteFromDatabase()
{
    qDebug() << "Deleting row id "+QString::number(m_id)+" from "+m_table->name()+".";
    QSqlQuery deletion = query(QString("DELETE FROM %1 WHERE id = %2").arg(m_table->name()).arg(m_id));

    if(deletion.lastError().isValid())
    {
        qWarning() << "Deletion failed: " << deletion.lastError();
    }

    deletion.finish();
    m_id = -1;
}

} // namespace Database
