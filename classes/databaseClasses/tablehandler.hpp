/**
 * @file tablehandler.hpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Header file for the TableHandler class.
 *
 * @details This file contains the declaration of the TableHandler class, which is a part of the application's backend logic.
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

#pragma once

#include <QDebug>
#include <QtSql>

#include "databasehandler.hpp"
#include "../backendClasses/logger.hpp"

//--------------------------------------------------------------------------------------------------------------------//
namespace AposDatabase {
    /**
     * @class TableHandler
     * @ingroup Database-Functions
     * @brief Provides the functionality for generating a table model, inserting into a table, and getting the active table name, table model, and last table error.
     * @details The TableHandler class is a part of the application's backend logic.
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
    class TableHandler {
    public:
        /**
         * @brief Constructor for the TableHandler class.
         * @ingroup Constructructors-Destructors
         * @details This constructor initializes the TableHandler object with a DatabaseHandler object.
         * @param newDbHandler Shared pointer to the DatabaseHandler object.
         */
        TableHandler(QSharedPointer<DatabaseHandler> newDbHandler, QSharedPointer<AposLogger::Logger> newLogger);

        /**
         * @brief Constructor for the TableHandler class.
         * @ingroup Constructructors-Destructors
         * @details This constructor initializes the TableHandler object with a DatabaseHandler object and a table name.
         * @param newDbHandler Shared pointer to the DatabaseHandler object.
         * @param tableName The name of the table.
         */
        TableHandler(QSharedPointer<DatabaseHandler> newDbHandler,
                     const QString &tableName,
                     QSharedPointer<AposLogger::Logger> newLogger);

        /**
         * @brief Destructor for the TableHandler class.
         * @ingroup Constructructors-Destructors
         * @details This destructor cleans up the TableHandler object.
         */
        ~TableHandler();

        /**
         * @brief Generates a table model.
         * @ingroup Database-Functions
         * @details This function generates a table model for the TableHandler object.
         */
        void generateTableModel();

        /**
         * @brief Generates a table model with a specified table name.
         * @ingroup Database-Functions
         * @details This function generates a table model for the TableHandler object with a specified table name.
         * @param tableName The name of the table.
         */
        void generateTableModel(const QString &tableName);

        /**
         * @brief Inserts into a table.
         * @ingroup Database-Functions
         * @details This function inserts into a table with specified values.
         * @param tableName The name of the table.
         * @param value1 The first value to insert.
         * @param value2 The second value to insert.
         * @param value3 The third value to insert.
         * @param value4 The fourth value to insert.
         * @param value5 The fifth value to insert.
         * @return Boolean value indicating whether the insertion was successful.
         */
        bool insertIntoTable(const QString &tableName, const QString &value1, const QString &value2,
                             const QString &value3, const QString &value4, const QString &value5);

        /**
         * @brief Sets the active table name.
         * @ingroup Setter
         * @details This function sets the active table name of the TableHandler object.
         * @param newActiveTableName The new active table name.
         */
        void setActiveTableName(const QString &newActiveTableName);

        /**
         * @brief Gets the table model.
         * @ingroup Getter
         * @details This function gets the table model of the TableHandler object.
         * @return Shared pointer to the QSqlTableModel object.
         */
        QSharedPointer<QSqlTableModel> getTableModel();

        /**
         * @brief Gets the active table name.
         * @ingroup Getter
         * @details This function gets the active table name of the TableHandler object.
         * @return The active table name.
         */
        [[nodiscard]] const QString &getActiveTableName() const;

        /**
         * @brief Gets the last table error.
         * @ingroup Getter
         * @details This function gets the last table error of the TableHandler object.
         * @return The last table error.
         */
        [[nodiscard]] const QSqlError &getLastTableError() const;

    private:
        /**
         * @brief The active table name of the TableHandler object.
         * @ingroup Variables
         * @details This variable is used to store the active table name of the TableHandler object.
         */
        QString activeTableName = "userTable";

        /**
         * @brief Shared pointer to the DatabaseHandler object.
         * @ingroup Variables
         * @details This shared pointer is used to access the DatabaseHandler object.
         */
        QSharedPointer<DatabaseHandler> ptrDbHandler;

        /**
         * @brief Shared pointer to the QSqlTableModel object.
         * @ingroup Variables
         * @details This shared pointer is used to access the QSqlTableModel object.
         */
        QSharedPointer<QSqlTableModel> ptrTableModel;

        /**
         * @brief Shared pointer to the Logger object.
         * @ingroup Variables
         * @details This shared pointer is used to access the Logger object.
         */
        QSharedPointer<AposLogger::Logger> ptrLogger;

        /**
         * @brief The last table error of the TableHandler object.
         * @ingroup Variables
         * @details This variable is used to store the last table error of the TableHandler object.
         */
        QSqlError lastTableError;
    };
}