/**
 * @file databasehandler.hpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Header file for the DatabaseHandler class.
 *
 * @details This file contains the declaration of the DatabaseHandler class, which is a part of the application's backend logic.
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

#pragma once

#include <QDebug>
#include <QtSql>

//--------------------------------------------------------------------------------------------------------------------//
namespace AposDatabase {
    /**
     * @class DatabaseHandler
     * @ingroup Database-Functions
     * @brief Provides the functionality for initializing and closing the database, executing SQL commands, and getting the active database and SQL error.
     * @details The DatabaseHandler class is a part of the application's backend logic.
     *
     * @see QtSql
     * @see QSqlDatabase
     * @see QSqlError
     * @see QSharedPointer
     * @see QDebug
     */
    class DatabaseHandler {
    public:
        /**
         * @brief Constructor for the DatabaseHandler class.
         * @ingroup Constructructors-Destructors
         * @details This constructor initializes the DatabaseHandler object.
         */
        DatabaseHandler();

        /**
         * @brief Initializes the database.
         * @ingroup Initialization
         * @details This function initializes the database of the DatabaseHandler object.
         * @return Boolean value indicating whether the database is initialized.
         */
        bool initDatabase();

        /**
         * @brief Closes the database.
         * @ingroup Database-Functions
         * @details This function closes the database of the DatabaseHandler object.
         */
        void closeDatabase();

        /**
         * @brief Executes a SQL command.
         * @ingroup Database-Functions
         * @details This function executes a specified SQL command.
         * @param command The SQL command to execute.
         * @return Boolean value indicating whether the command was executed successfully.
         */
        bool executeCommand(const QString &command);

        /**
         * @brief Gets the active database.
         * @ingroup Getter
         * @details This function gets the active database of the DatabaseHandler object.
         * @return Shared pointer to the active QSqlDatabase object.
         */
        QSharedPointer<QSqlDatabase> getActiveDatabase();

        /**
         * @brief Gets the SQL error.
         * @ingroup Getter
         * @details This function gets the SQL error of the DatabaseHandler object.
         * @return The SQL error.
         */
        [[nodiscard]] const QSqlError &getSqlError() const;
    private:
        /**
         * @brief The SQL error of the DatabaseHandler object.
         * @ingroup Variables
         * @details This variable is used to store the SQL error of the DatabaseHandler object.
         */
        QSqlError lastSqlError;

        /**
         * @brief The active database of the DatabaseHandler object.
         * @ingroup Variables
         * @details This variable is used to store the active database of the DatabaseHandler object.
         */
        QSqlDatabase activeDatabase;

        /**
         * @brief Shared pointer to the active database.
         * @ingroup Variables
         * @details This shared pointer is used to access the active database of the DatabaseHandler object.
         */
        QSharedPointer<QSqlDatabase> ptrActiveDatabase;

        /**
         * @brief The path to the database.
         * @ingroup Variables
         * @details This variable is used to store the path to the database.
         */
        QString databasePath = R"(C:\Users\Clean\Documents\Projekte\Apos-DatabaseManager\Project\resources\defaultDatabase\userDatabase.db)";
    };
}