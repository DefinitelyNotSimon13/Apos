#include "databasehandler.hpp"

DatabaseHandler::DatabaseHandler()
{

}

bool DatabaseHandler::initDatabase()
{
    activeDatabase = QSqlDatabase::addDatabase("QSQLITE", "connection1");
    activeDatabase.setDatabaseName(databasePath);

    if (!activeDatabase.open())
    {
        lastSqlError = activeDatabase.lastError();
        qDebug() << lastSqlError.text();
        return false;
    }
    else
    {
        return true;
    }
}

void DatabaseHandler::closeDatabase()
{
    activeDatabase.close();
    activeDatabase = QSqlDatabase();
}

bool DatabaseHandler::executeCommand(QString command)
{
    QSqlQuery query(activeDatabase);
    if (!query.exec(command))
    {
        lastSqlError = query.lastError();
        qDebug() << lastSqlError.text();
        return false;
    }
    return true;
}

const QSqlDatabase &DatabaseHandler::getActiveDatabase() const
{
    return activeDatabase;
}

const QSqlError &DatabaseHandler::getSqlError() const
{
    return lastSqlError;
}

void DatabaseHandler::setDatabasePath(const QString &newDatabasePath)
{
   databasePath = newDatabasePath;
}

void DatabaseHandler::setLastSqlError(const QSqlError &newLastSqlError)
{
    lastSqlError = newLastSqlError;
}
