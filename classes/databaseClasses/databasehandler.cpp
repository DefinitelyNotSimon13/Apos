/**
 * @file databasehandler.cpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Source file for the DatabaseHandler class.
 *
 * @details This file contains the implementation of the DatabaseHandler class, which is a part of the application's backend logic.
 * The DatabaseHandler class provides the functionality for initializing and closing the database, executing SQL commands, and getting the active database and SQL error.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see QtSql
 * @see QSqlDatabase
 * @see QSqlError
 * @see QSharedPointer
 * @see QDebug
 */
#include "databasehandler.hpp"

namespace AposDatabase {
    //----------------------------------------------------------------------------------------------------------------//
    DatabaseHandler::DatabaseHandler() = default;
    //----------------------------------------------------------------------------------------------------------------//
    bool DatabaseHandler::initDatabase() {

        activeDatabase = QSqlDatabase::addDatabase("QSQLITE", "db1");
        activeDatabase.setDatabaseName(databasePath);
        ptrActiveDatabase = QSharedPointer<QSqlDatabase>(&activeDatabase);
        return activeDatabase.open();
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DatabaseHandler::closeDatabase() {
        activeDatabase.close();
        QSqlDatabase::removeDatabase("db1");
    }
    //----------------------------------------------------------------------------------------------------------------//
    bool DatabaseHandler::executeCommand(const QString &command) {
        bool queryExecuted = false;
        QSqlQuery query(activeDatabase);
        if (!query.exec(command)) {
            lastSqlError = query.lastError();
            qDebug() << lastSqlError.text();
            queryExecuted = false;
        } else {
            queryExecuted = true;
        }
        return queryExecuted;
    }
    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<QSqlDatabase> DatabaseHandler::getActiveDatabase() {
        return ptrActiveDatabase;
    }
    //----------------------------------------------------------------------------------------------------------------//
    const QSqlError &DatabaseHandler::getSqlError() const {
        return lastSqlError;
    }
}
