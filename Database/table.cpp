#include "table.h"

namespace Database {

TableBase::TableBase(const QString &name) :
    AttributeOwner(),
    m_name(name)
{

}

QString TableBase::name() const
{
    return m_name;
}

int TableBase::rowCount() const
{
    QSqlQuery q = query("SELECT COUNT(id) FROM "+m_name);
    q.first();
    int count = q.value(0).toInt();
    q.finish();
    return count;
}

QList<AttributeBase*> TableBase::attributes() const
{
    return QList<AttributeBase*>();
}


AttributeBase *TableBase::attribute(const QString &/*name*/) const
{
    return 0;
}

QSqlQuery TableBase::query(const QString &queryString) const
{
    QSqlQuery query(Database::instance()->sqlDatabaseLocked());
    query.exec(queryString);
    Database::instance()->releaseDatabaseLock();

    if(query.lastError().isValid())
    {
	qWarning() << "Table::query: Could not run query.";
	qWarning() << "Table::query: " << query.lastError();
	qWarning() << "Table::query: " << queryString;
	return QSqlQuery();
    }

    return query;
}

void TableBase::createTableIfNotExists()
{
    QSqlQuery select(Database::instance()->sqlDatabaseLocked());

    //Prüfe, ob der Name dieser Tabelle in der Datenbank existiert...
    QString query = "SELECT name FROM sqlite_master WHERE name='" + m_name + "';";
    select.exec(query);
    Database::instance()->releaseDatabaseLock();

    select.first();

    //... falls nicht muss die Tabelle initialisiert werden.
    if(select.lastError().isValid() || !select.value(0).isValid())
    {
	qDebug() << "TableInterface::createTableIfNotExists: Table does not exist: " << m_name;
	createTable();
    }
    select.finish();
}

void TableBase::addColumn(AttributeBase * attribute)
{
    qDebug() << "TableInterface::addcolumn: Adding new column" << attribute->name() << "to table" << m_name;
    QSqlQuery alter(Database::instance()->sqlDatabaseLocked());

    QString query = "ALTER TABLE " + m_name + " ADD " + attribute->name() + " " + attribute->sqlType();
    qDebug() << query;
    alter.exec(query);
    Database::instance()->releaseDatabaseLock();

    alter.first();

    if(alter.lastError().isValid())
    {
	qDebug() << "TableInterface::addColumn: Alter failed for table" << m_name;
	qDebug() << "TableInterface::addColumn:" << alter.lastError();
    }
}

void TableBase::deleteRow(Row *row)
{
    foreach(Row* row, row->childRows())
    {
	deleteRow(row);
    }

    qDebug() << "Deleting row id "+QString::number(row->id())+" from "+m_name+".";
    QSqlQuery deletion = query(QString("DELETE FROM %1 WHERE id = %2").arg(m_name).arg(row->id()));

    if(deletion.lastError().isValid())
    {
	qWarning() << "Deletion failed: " << deletion.lastError();
    }

    deletion.finish();
    row->m_id = -1;
}

RowRegistrar::RowRegistrar(TableBase* table, Row *row)
{
    table->registerRowType(row);
}

} // namespace Database
