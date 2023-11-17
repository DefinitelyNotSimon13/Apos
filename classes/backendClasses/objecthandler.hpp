/**
 * @file ObjectHandler.hpp
 * @brief Header file for the ObjectHandler class.
 * @date 14.11.2023
 * @version 1.1.1
 * @author Simon Blum
 */

#pragma once

#include <QApplication>
#include <QDebug>
#include <QtSql>

#include "databaseClasses/databasehandler.hpp"
#include "tableClasses/tablehandler.hpp"

/**
 * @defgroup ObjectHandlerGroup ObjectHandler
 * @{
 */

/**
 * @brief The ObjectHandler class manages application objects related to database interactions.
 * @details This class handles the initialization of the database and table objects.
 */
class ObjectHandler
{
public:

    /**
     * @addtogroup ConstructorsDestructorsGroup
     * @{
     */

    /**
     * @brief Constructs an ObjectHandler object.
     * @details Initializes an instance of ObjectHandler.
     */
    ObjectHandler(QApplication* newApplication, DatabaseHandler* newDBHandler, TableHandler* newTableHandler);

    /// @}

    /**
     * @addtogroup SetterGroup
     * @{
     */

    /**
     * @brief Sets the active table name.
     * @param newActiveTableName The new active table name.
     */
    void setActiveTableName(const QString &newActiveTableName);

    /// @}

    /**
     * @addtogroup InitializationGroup
     * @{
     */

    /**
     * @brief Initializes the DatabaseHandler object.
     * @details Sets the database path, active table name, and initializes the database.
     *
     * @return True if the database initialization is successful, false otherwise.
     */
    bool initDatabaseObject();

    /**
     * @brief Initializes the TableHandler object with the active database and table name.
     * @details Generates a table model using the active database and table name.
     *
     * @return Always returns true.
     */
    bool initTableObject();

    /**
     * @brief Initializes the TableHandler object with the provided database and table name.
     * @details Generates a table model using the provided database and table name.
     *
     * @param inputActiveDatabase The database to use.
     * @param inputTableName The name of the table.
     * @return Always returns true.
     */
    bool initTableObject(QSqlDatabase inputActiveDatabase, const QString &inputTableName);

    /// @}

    /**
     * @addtogroup GetterGroup
     * @{
     */

    /**
     * @brief Retrieves the active database.
     * @return The active database.
     */
    const QSqlDatabase &getActiveDatabase() const;

    /**
     * @brief Retrieves the TableHandler instance.
     * @return The TableHandler instance.
     */
    TableHandler *getTableHandler() const;

    /**
     * @brief Retrieves the DatabaseHandler instance.
     * @return The DatabaseHandler instance.
     */
    DatabaseHandler *getDbHandler() const;

    /**
     * @brief Retrieves the active table name.
     * @return The active table name.
     */
    const QString &getActiveTableName() const;

    const QSqlError& getTableSqlError() const;

    QApplication *application; /**< The QApplication instance. */

    /// @}

private:


    DatabaseHandler *dbHandler; /**< The DatabaseHandler instance. */
    TableHandler *tableHandler; /**< The TableHandler instance. */

};

/**
 * @} // end of ObjectHandlerGroup
 */
