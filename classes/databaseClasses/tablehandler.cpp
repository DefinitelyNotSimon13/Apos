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
    TableHandler::TableHandler(QSharedPointer<DatabaseHandler> newDbHandler) {
        ptrDbHandler = std::move(newDbHandler);
    }
    //----------------------------------------------------------------------------------------------------------------//
    TableHandler::TableHandler(QSharedPointer<DatabaseHandler> newDbHandler, const QString &tableName) {
        ptrDbHandler = std::move(newDbHandler);
        activeTableName = tableName;
        ptrTableModel = QSharedPointer<QSqlTableModel>(
                new QSqlTableModel(nullptr, *ptrDbHandler->getActiveDatabase()));
        ptrTableModel->setTable(tableName);
        if (!ptrTableModel->select()) {
            throw std::runtime_error("Failed to select table");
        }
    }
    //----------------------------------------------------------------------------------------------------------------//
    TableHandler::~TableHandler() {
        ptrTableModel = nullptr;
        qDebug() << "TableHandler destroyed";
    }
    //----------------------------------------------------------------------------------------------------------------//
    void TableHandler::generateTableModel() {
        ptrTableModel = QSharedPointer<QSqlTableModel>(new QSqlTableModel(nullptr, *ptrDbHandler->getActiveDatabase()));
        ptrTableModel->setTable(activeTableName);
        if (!ptrTableModel->select()) {
            throw std::runtime_error("Failed to select table");
        }
    }
    //----------------------------------------------------------------------------------------------------------------//
    void TableHandler::generateTableModel(const QString &tableName) {
        activeTableName = tableName;
        ptrTableModel = QSharedPointer<QSqlTableModel>(new QSqlTableModel(nullptr, *ptrDbHandler->getActiveDatabase()));
        ptrTableModel.data()->setTable(activeTableName);
        if (!ptrTableModel.data()->select()) {
            qDebug() << "Failed to select table:" << ptrTableModel->lastError();
            throw std::runtime_error("Failed to select table");
        }
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

        } else {
            query.bindValue(":value1", value1);
            query.bindValue(":value2", value2);
            query.bindValue(":value3", value3);
            query.bindValue(":value4", value4);
            query.bindValue(":value5", value5);
            if (!query.exec()) {
                lastTableError = query.lastError();
                querrySuccess = false;
            } else {
                querrySuccess = true;
            }
        }
        return querrySuccess;
    }
    //----------------------------------------------------------------------------------------------------------------//
    const QString &TableHandler::getActiveTableName() const {
        return activeTableName;
    }
    //----------------------------------------------------------------------------------------------------------------//
    void TableHandler::setActiveTableName(const QString &newActiveTableName) {
        activeTableName = newActiveTableName;
    }
    //----------------------------------------------------------------------------------------------------------------//
    const QSqlError &TableHandler::getLastTableError() const {
        return lastTableError;
    }
    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<QSqlTableModel> TableHandler::getTableModel() {
        return ptrTableModel;
    }
}
