/**
 * @file objecthandler.hpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Header file for the ObjectHandler class.
 *
 * @details This file contains the declaration of the ObjectHandler class, which is a part of the application's backend logic.
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

#pragma once

#include <QApplication>
#include <QDebug>
#include <QtSql>

#include "../databaseClasses/databasehandler.hpp"
#include "../databaseClasses/tablehandler.hpp"
#include "logger.hpp"

//--------------------------------------------------------------------------------------------------------------------//
namespace AposBackend {
    /**
     * @class ObjectHandler
     * @ingroup Database-Functions
     * @brief The ObjectHandler class is a part of the application's backend logic.
     * @details Provides the functionality for initializing the database and table objects, setting the active table name,
     * and getting the active database, table handler, database handler, active table name, and table SQL error.
     *
     * @see AposDatabase::DatabaseHandler
     * @see AposDatabase::TableHandler
     * @see QApplication
     * @see QSharedPointer
     * @see QDebug
     * @see QtSql
     */
    class ObjectHandler {
    public:
        /**
         * @brief Constructor for the ObjectHandler class.
         * @ingroup Constructructors-Destructors
         * @details This constructor initializes the ObjectHandler object with a QApplication object, a DatabaseHandler object, and a TableHandler object.
         * @param newApplication Shared pointer to the QApplication object.
         * @param newDbHandler Shared pointer to the DatabaseHandler object.
         * @param newTableHandler Shared pointer to the TableHandler object.
         * @param newLogger Shared pointer to the Logger object.
         */
        ObjectHandler(QSharedPointer<QApplication> newApplication,
                      QSharedPointer<AposDatabase::DatabaseHandler> newDbHandler,
                      QSharedPointer<AposDatabase::TableHandler> newTableHandler,
                      QSharedPointer<AposLogger::Logger> newLogger);

        /**
         * @brief Initializes the database object.
         * @ingroup Initialization
         * @details This function initializes the database object of the ObjectHandler object.
         * @return Boolean value indicating whether the database object is initialized.
         */
        bool initDatabaseObject();

        /**
         * @brief Initializes the table object.
         * @ingroup Initialization
         * @details This function initializes the table object of the ObjectHandler object with a specified table name.
         * @param inputTableName The name of the table.
         * @return Boolean value indicating whether the table object is initialized.
         */
        bool initTableObject(const QString &inputTableName);

        /**
         * @brief Sets the active table name.
         * @ingroup Setter
         * @details This function sets the active table name of the ObjectHandler object.
         * @param newActiveTableName The new active table name.
         */
        [[maybe_unused]] void setActiveTableName(const QString &newActiveTableName);

        /**
         * @brief Gets the active database.
         * @ingroup Getter
         * @details This function gets the active database of the ObjectHandler object.
         * @return Shared pointer to the active QSqlDatabase object.
         */
        [[maybe_unused]] [[nodiscard]] QSharedPointer<QSqlDatabase> getActiveDatabase() const;

        /**
         * @brief Gets the table handler.
         * @ingroup Getter
         * @details This function gets the table handler of the ObjectHandler object.
         * @return Shared pointer to the TableHandler object.
         */
        [[nodiscard]] QSharedPointer<AposDatabase::TableHandler> getPtrTableHandler() const;

        /**
         * @brief Gets the database handler.
         * @ingroup Getter
         * @details This function gets the database handler of the ObjectHandler object.
         * @return Shared pointer to the DatabaseHandler object.
         */
        [[nodiscard]] QSharedPointer<AposDatabase::DatabaseHandler> getPtrDbHandler() const;

        /**
         * @brief Gets the active table name.
         * @ingroup Getter
         * @details This function gets the active table name of the ObjectHandler object.
         * @return The active table name.
         */
        [[nodiscard]] const QString &getActiveTableName() const;

        /**
         * @brief Gets the table SQL error.
         * @ingroup Getter
         * @details This function gets the table SQL error of the ObjectHandler object.
         * @return The table SQL error.
         */
        [[nodiscard]] const QSqlError &getTableSqlError() const;

        /**
         * @brief Gets the QApplication object.
         * @ingroup Getter
         * @details This function gets the QApplication object of the ObjectHandler object.
         * @return Shared pointer to the QApplication object.
         */
        [[nodiscard]] const QSharedPointer<QApplication> &getPtrApplication() const;

    private:
        /**
         * @brief Shared pointer to the QApplication object.
         * @ingroup Variables
         * @details This shared pointer is used to access the QApplication object.
         */
        QSharedPointer<QApplication> ptrApplication;

        /**
         * @brief Shared pointer to the DatabaseHandler object.
         * @ingroup Variables
         * @details This shared pointer is used to access the DatabaseHandler object.
         */
        QSharedPointer<AposDatabase::DatabaseHandler> ptrDbHandler;

        /**
         * @brief Shared pointer to the TableHandler object.
         * @ingroup Variables
         * @details This shared pointer is used to access the TableHandler object.
         */
        QSharedPointer<AposDatabase::TableHandler> ptrTableHandler;

        /**
         * @brief Shared pointer to the Logger object.
         * @ingroup Variables
         * @details This shared pointer is used to access the Logger object.
         */
        QSharedPointer<AposLogger::Logger> ptrLogger;
    };
}