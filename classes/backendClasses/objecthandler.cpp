/**
 * @file objecthandler.cpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Source file for the ObjectHandler class.
 *
 * @details This file contains the implementation of the ObjectHandler class, which is a part of the application's backend logic.
 * The ObjectHandler class provides the functionality for initializing the database and table objects, setting the active table name,
 * and getting the active database, table handler, database handler, active table name, and table SQL error.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see AposDatabase::DatabaseHandler
 * @see AposDatabase::TableHandler
 * @see QApplication
 * @see QSharedPointer
 * @see QDebug
 * @see QtSql
 */
#include "objecthandler.hpp"

namespace AposBackend {
    //----------------------------------------------------------------------------------------------------------------//
    ObjectHandler::ObjectHandler(QSharedPointer<QApplication> newApplication,
                                 QSharedPointer<AposDatabase::DatabaseHandler> newDbHandler,
                                 QSharedPointer<AposDatabase::TableHandler> newTableHandler,
                                 QSharedPointer<AposLogger::Logger> newLogger) :
            ptrApplication(qMove(newApplication)),
            ptrDbHandler(qMove(newDbHandler)),
            ptrTableHandler(qMove(newTableHandler)),
            ptrLogger(qMove(newLogger)) {
        ptrLogger->log("init", "ObjectHandler initialized");
    }

    //----------------------------------------------------------------------------------------------------------------//
    bool ObjectHandler::initDatabaseObject() {
        bool initializedDatabaseObject = false;
        initializedDatabaseObject = ptrDbHandler->initDatabase();
        ptrLogger->log("init", "DatabaseHandler initialized");
        return initializedDatabaseObject;
    }

    //----------------------------------------------------------------------------------------------------------------//
    bool ObjectHandler::initTableObject(const QString &inputTableName) {
        bool initializedTableObject;
        try {
            ptrTableHandler->generateTableModel(inputTableName);
            initializedTableObject = true;
        }
        catch (const QException &e) {
            ptrLogger->log("caught exception", e.what());
            initializedTableObject = false;
        }
        return initializedTableObject;

    }

    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<AposDatabase::TableHandler> ObjectHandler::getPtrTableHandler() const {
        ptrLogger->log("status", "ObjectHandler");
        return ptrTableHandler;
    }

    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<AposDatabase::DatabaseHandler> ObjectHandler::getPtrDbHandler() const {
        ptrLogger->log("status", "ObjectHandler");
        return ptrDbHandler;
    }

    //----------------------------------------------------------------------------------------------------------------//
    const QString &ObjectHandler::getActiveTableName() const {
        ptrLogger->log("status", "ObjectHandler");
        return ptrTableHandler->getActiveTableName();
    }

    //----------------------------------------------------------------------------------------------------------------//
    const QSqlError &ObjectHandler::getTableSqlError() const {
        ptrLogger->log("status", "ObjectHandler");
        return ptrTableHandler->getLastTableError();
    }

    //----------------------------------------------------------------------------------------------------------------//
    [[maybe_unused]] QSharedPointer<QSqlDatabase> ObjectHandler::getActiveDatabase() const {
        ptrLogger->log("status", "ObjectHandler");
        return ptrDbHandler->getActiveDatabase();
    }

    //----------------------------------------------------------------------------------------------------------------//
    [[maybe_unused]] void ObjectHandler::setActiveTableName(const QString &newActiveTableName) {
        ptrLogger->log("status", "ObjectHandler");
        ptrTableHandler->setActiveTableName(newActiveTableName);
    }

    //----------------------------------------------------------------------------------------------------------------//
    const QSharedPointer<QApplication> &ObjectHandler::getPtrApplication() const {
        ptrLogger->log("status", "ObjectHandler");
        return ptrApplication;
    }

}




