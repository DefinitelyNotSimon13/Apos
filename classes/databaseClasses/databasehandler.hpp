/**
 * @file DatabaseHandler.hpp
 * @brief Header file for the DatabaseHandler class.
 * @date 13.11.2023
 * @version 1.1.1
 * @author Simon Blum
 */

#pragma once

#include <QDebug>
#include <QtSql>

/**
 * @addtogroup DatabaseHandlerGroup
 * @{
 */

/**
 * @brief The DatabaseHandler class manages database-related operations.
 */
class DatabaseHandler
{
public:

    /**
     * @addtogroup ConstructorsDestructorsGroup
     * @{
     */

    /**
     * @brief Constructs a DatabaseHandler object.
     */
    DatabaseHandler();

    ///@}

    /**
     * @addtogroup InitializationGroup
     * @{
     */

    /**
     * @brief Initializes the SQLite database.
     * @return True if the database is successfully initialized; otherwise, false.
     */
    bool initDatabase();

    /// @}

    /**
     * @brief Closes the active SQLite database.
     */
    void closeDatabase();

    /**
     * @addtogroup CommandExecutionGroup
     * @{
     */

    /**
     * @brief Executes an SQL command on the active database.
     * @param command The SQL command to execute.
     * @return True if the command is executed successfully; otherwise, false.
     */
    bool executeCommand(QString command);

    /// @}

    /**
     * @addtogroup GetterGroup
     * @{
     */

    /**
     * @brief Retrieves the active database.
     * @return The active QSqlDatabase instance.
     */
    const QSqlDatabase &getActiveDatabase() const;

    /**
     * @brief Retrieves the last SQL error.
     * @return The last QSqlError instance.
     */
    const QSqlError &getSqlError() const;

    /// @}

    /**
     * @addtogroup SetterGroup
     * @{
     */

    /**
     * @brief Sets the path for the SQLite database file.
     * @param newDatabasePath The new path for the database file.
     */
    void setDatabasePath(const QString &newDatabasePath);

    ///@}

    void setLastSqlError(const QSqlError &newLastSqlError);

private:

    QSqlError lastSqlError; /**< The last SQL error. */

    QSqlDatabase activeDatabase; /**< The active QSqlDatabase instance. */

    QString databasePath = R"(C:\Users\user\Desktop\Simon\ArosDatabasemanager\resources\userDatabase.db)"; /**< The path to the SQLite database file. */

};

/**
 * @} // end of DatabaseHandlerGroup
 */
