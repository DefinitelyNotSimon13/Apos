#include "tablehandler.hpp"

TableHandler::TableHandler()
{

}

TableHandler::TableHandler(const QSqlDatabase& newActiveDatabase, const QString &tableName)
{
    tblActiveDatabase = newActiveDatabase;
    activeTableName = tableName;
    tableModel = new QSqlTableModel(nullptr, tblActiveDatabase);
    tableModel->setTable(tableName);
    tableModel->select();
}

void TableHandler::generateTableModel()
{
    tableModel = new QSqlTableModel(nullptr, tblActiveDatabase);
    tableModel->setTable(activeTableName);
    tableModel->select();
}

void TableHandler::generateTableModel(QSqlDatabase& activeDatabase, const QString &tableName)
{
    tblActiveDatabase = activeDatabase;
    activeTableName = tableName;
    tableModel = new QSqlTableModel(nullptr, activeDatabase);
    tableModel->setTable(tableName);
    tableModel->select();
}

bool TableHandler::insertIntoTable(const QString &tableName, const QString &value1, const QString &value2,
                                   const QString &value3, const QString &value4, const QString &value5)
{
    QSqlQuery query(tblActiveDatabase);
    query.prepare(QString("INSERT INTO %1 VALUES (:value1, :value2, :value3, :value4, :value5)").arg(tableName));
    query.bindValue(":value1", value1);
    query.bindValue(":value2", value2);
    query.bindValue(":value3", value3);
    query.bindValue(":value4", value4);
    query.bindValue(":value5", value5);
    if(!query.exec()){
        lastTableError = query.lastError();
        return false;
    }
    return true;
}

const QString &TableHandler::getActiveTableName() const
{
    return activeTableName;
}

void TableHandler::setActiveTableName(const QString &newActiveTableName)
{
    activeTableName = newActiveTableName;
}

const QSqlDatabase &TableHandler::getTblActiveDatabase() const
{
    return tblActiveDatabase;
}

const QSqlError &TableHandler::getLastTableError() const
{
    return lastTableError;
}

QSqlTableModel *TableHandler::getTableModel() const
{
    return tableModel;
}

