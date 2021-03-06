#include "row.h"

#include "attribute.h"
#include "table.h"

#include <Gui/Details/detailswidget.h>
#include <Gui/Details/rowwidget.h>
#include <Gui/Details/rowwindow.h>
#include <Gui/Details/statswidget.h>
#include <Gui/Details/summarywidget.h>

namespace Database {

Row::Row(int id, TableBase *table) :
    AttributeOwner(table),
    m_id(id),
    m_table(table),
    m_attributes(QHash<QString, AttributeBase* >())
{
}

const int& Row::id() const
{
    return m_id;
}

void Row::setId(int id)
{
    m_id = id;
    emit idChanged(id);
}

QSqlQuery Row::query(const QString &queryString) const
{
    return m_table->query(queryString);
}

bool Row::set(const QString &key, const QVariant &value)
{
    return set(key,value,QLatin1String("id = ")+QString::number(m_id));
}

bool Row::set(const QString &key, const QVariant &value, const QString &condition)
{
    if(m_id > 0)
    {
        QSqlQuery q = query(QLatin1String("UPDATE ")+m_table->name()+
                            QLatin1String(" SET ")+key+
                            QLatin1String(" = '")+value.toString()+
                            QLatin1String("' WHERE ")+condition+
                            QLatin1String(";"));
	q.finish();
	return q.isValid();
    }

    return false;
}

QVariant Row::get(const QString &key) const
{
    QVariant value = get(key, QLatin1String("id = ")+QString::number(m_id));
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
    QSqlQuery select = query(QLatin1String("SELECT ")+key+
                             QLatin1String(" FROM ")+m_table->name()+
                             QLatin1String(" WHERE ")+condition+
                             QLatin1String(";"));

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

QList<Row*> Row::childRows() const
{
    return m_childRows;
}

void Row::addChildRow(Row *row)
{
    m_childRows.append(row);

    if(m_id != 0)
    {
        row->table()->insertRow(row);
    }
}

void Row::addChildRows(QList<Row *> rows)
{
    m_childRows.append(rows);
}

Gui::Details::DetailsWidget* Row::detailsWidget()
{
    return 0;
}

Gui::Details::RowWidget* Row::rowWidget()
{
    return new Gui::Details::RowWidget(this);
}

Gui::Details::RowWindow* Row::rowWindow()
{
    return new Gui::Details::RowWindow(this);
}

Gui::Details::StatsWidget* Row::statsWidget()
{
    return 0;
}

Gui::Details::SummaryWidget* Row::summaryWidget()
{
    return 0;
}

TableBase *Row::table() const
{
    return m_table;
}

} // namespace Database
