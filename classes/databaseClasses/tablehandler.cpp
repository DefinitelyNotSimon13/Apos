/**
 * @file tablehandler.cpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Source file for the TableHandler class.
 *
 * @details This file contains the implementation of the TableHandler class, which is a part of the application's backend logic.
 * The TableHandler class provides the functionality for generating a table model, inserting into a table, and getting the active table name, table model, and last table error.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see DatabaseHandler
 * @see QSharedPointer
 * @see QDebug
 * @see QtSql
 * @see QSqlTableModel
 * @see QSqlError
 * @see QSqlQuery
 * @see QSqlDatabase
 */
#include "tablehandler.hpp"

#include <utility>

namespace AposDatabase {
    //----------------------------------------------------------------------------------------------------------------//
    TableHandler::TableHandler(QSharedPointer<DatabaseHandler> newDbHandler,
                               QSharedPointer<AposLogger::Logger> newLogger)
            : ptrLogger(qMove(newLogger)),
              ptrDbHandler(qMove(newDbHandler)) {
        ptrLogger->log("init", "TableHandler initialized");
    }

    //----------------------------------------------------------------------------------------------------------------//
    TableHandler::TableHandler(QSharedPointer<DatabaseHandler> newDbHandler,
                               const QString &tableName,
                               QSharedPointer<AposLogger::Logger> newLogger)
            : ptrLogger(qMove(newLogger)),
              ptrDbHandler(qMove(newDbHandler)) {
        activeTableName = tableName;
        ptrTableModel = QSharedPointer<QSqlTableModel>(
                new QSqlTableModel(nullptr, *ptrDbHandler->getActiveDatabase()));
        ptrLogger->log("init", "ptrTableModel initialized");

        ptrTableModel->setTable(tableName);
        if (!ptrTableModel->select()) {
            ptrLogger->error("Failed to select table" + ptrTableModel->lastError().text(),
                             "TableHandler()", "TableHandler", "");
        }
        ptrLogger->log("init", "TableHandler initialized and table model generated");
    }

    //----------------------------------------------------------------------------------------------------------------//
    TableHandler::~TableHandler() {
        ptrTableModel = nullptr;
        ptrLogger->log("status", "TableHandler destroyed");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void TableHandler::generateTableModel() {
        ptrTableModel = QSharedPointer<QSqlTableModel>(new QSqlTableModel(nullptr, *ptrDbHandler->getActiveDatabase()));
        ptrLogger->log("status", "ptrTableModel (re)initialized");

        ptrTableModel->setTable(activeTableName);
        if (!ptrTableModel->select()) {
            ptrLogger->error("Failed to select table" + ptrTableModel->lastError().text(),
                             "generateTableModel()", "TableHandler", "");
        }
        ptrLogger->log("status", "Table model generated");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void TableHandler::generateTableModel(const QString &tableName) {
        activeTableName = tableName;
        ptrTableModel = QSharedPointer<QSqlTableModel>(new QSqlTableModel(nullptr, *ptrDbHandler->getActiveDatabase()));
        ptrLogger->log("status", "ptrTableModel (re)initialized");

        ptrTableModel.data()->setTable(activeTableName);
        if (!ptrTableModel.data()->select()) {
            ptrLogger->error("Failed to select table" + ptrTableModel->lastError().text(),
                             "generateTableModel()", "TableHandler", "");
        }
        ptrLogger->log("status", "Table model generated");
    }

    //----------------------------------------------------------------------------------------------------------------//
    bool TableHandler::insertIntoTable(const QString &tableName, const QString &value1, const QString &value2,
                                       const QString &value3, const QString &value4, const QString &value5) {
        bool querrySuccess = false;
        QSqlQuery query(*ptrDbHandler->getActiveDatabase());
        if (!query.prepare(
                QString("INSERT INTO %1 VALUES (:value1, :value2, :value3, :value4, :value5)").arg(tableName))) {
            lastTableError = query.lastError();
            querrySuccess = false;
            ptrLogger->log("Error", "prepare query - " + lastTableError.text(), "insertIntoTable()", "TableHandler",
                           "");
        } else {
            query.bindValue(":value1", value1);
            query.bindValue(":value2", value2);
            query.bindValue(":value3", value3);
            query.bindValue(":value4", value4);
            query.bindValue(":value5", value5);
            if (!query.exec()) {
                lastTableError = query.lastError();
                querrySuccess = false;
                ptrLogger->log("Error", "execute query - " + lastTableError.text(), "insertIntoTable()", "TableHandler",
                               "");
            } else {
                querrySuccess = true;
                ptrLogger->log("status", "Query executed");
            }
        }
        return querrySuccess;
    }

    //----------------------------------------------------------------------------------------------------------------//
    const QString &TableHandler::getActiveTableName() const {
        ptrLogger->log("status", "Active table name requested");
        return activeTableName;
    }

    //----------------------------------------------------------------------------------------------------------------//
    void TableHandler::setActiveTableName(const QString &newActiveTableName) {
        ptrLogger->log("status", "Active table name set");
        activeTableName = newActiveTableName;
    }

    //----------------------------------------------------------------------------------------------------------------//
    const QSqlError &TableHandler::getLastTableError() const {
        ptrLogger->log("status", "Last table error requested");
        return lastTableError;
    }

    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<QSqlTableModel> TableHandler::getTableModel() {
        ptrLogger->log("status", "Table model requested");
        return ptrTableModel;
    }
}
