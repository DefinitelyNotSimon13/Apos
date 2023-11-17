/**
 * @file ObjectHandler.cpp
 * @brief Implementation file for the ObjectHandler class.
 * @date 14.11.2023
 * @version 1.1.1
 * @author Simon Blum
 */

#include "objecthandler.hpp"

ObjectHandler::ObjectHandler(QApplication* newApplication, DatabaseHandler* newDBHandler, TableHandler* newTableHandler)
{
    application = newApplication;
    dbHandler = newDBHandler;
    tableHandler = newTableHandler;
}

bool ObjectHandler::initDatabaseObject()
{
    if (!dbHandler->initDatabase())
    {
        return false;
    }
    return true;
}

bool ObjectHandler::initTableObject()
{
    QSqlDatabase db = getActiveDatabase();
    QString tn = getActiveTableName();
    tableHandler->generateTableModel(db, tn);
    return true;
}

bool ObjectHandler::initTableObject(QSqlDatabase inputActiveDatabase, const QString &inputTableName)
{
    tableHandler->generateTableModel(inputActiveDatabase, inputTableName);
    return true;
}

TableHandler *ObjectHandler::getTableHandler() const
{
    return tableHandler;
}

DatabaseHandler *ObjectHandler::getDbHandler() const
{
    return dbHandler;
}

const QString &ObjectHandler::getActiveTableName() const
{
    return tableHandler->getActiveTableName();
}

const QSqlError& ObjectHandler::getTableSqlError() const
{
    return tableHandler->getLastTableError();
}


const QSqlDatabase &ObjectHandler::getActiveDatabase() const
{
    return dbHandler->getActiveDatabase();
}

void ObjectHandler::setActiveTableName(const QString &newActiveTableName)
{
    tableHandler->setActiveTableName(newActiveTableName);
}

