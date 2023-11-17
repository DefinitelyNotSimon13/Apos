/**
 * @file TableHandler.hpp
 * @brief Header file for the TableHandler class.
 * @date 15.11.2023
 * @version 1.1.1
 * @author Simon Blum
 */

#pragma once

#include <QDebug>
#include <QtSql>

/**
 * @addtogroup TableHandlerGroup
 * @{
 */

/**
 * @brief The TableHandler class manages operations related to database tables.
 */
class TableHandler
{
public:

    /**
     * @addtogroup ConstructorsDestructorsGroup
     * @{
     */

    /**
     * @brief Constructs a TableHandler object.
     */
    TableHandler();

    /**
     * @brief Constructs a TableHandler object with an active database and table name.
     * @param activeDatabase The active QSqlDatabase.
     * @param tableName The name of the database table.
     */
    TableHandler(const QSqlDatabase& newActiveDatabase, const QString& tableName);

    ///@}

    /**
     * @name TableModelFunctions
     * @{
     */

    /**
     * @brief Generates a QSqlTableModel for the specified database and table name.
     */
    void generateTableModel();

    /**
     * @brief Generates a QSqlTableModel for the given database and table name.
     * @param activeDatabase The active QSqlDatabase.
     * @param tableName The name of the database table.
     */
    void generateTableModel(QSqlDatabase& activeDatabase, const QString &tableName);

    /// @}

    /**
     * @addtogroup GetterGroup
     * @{
     */

    /**
     * @brief Retrieves the QSqlTableModel associated with the TableHandler.
     * @return The QSqlTableModel instance.
     */
    QSqlTableModel *getTableModel() const;



    /**
     * @brief Retrieves the last QSqlError associated with the TableHandler.
     * @return The last QSqlError instance.
     */
    const QSqlError &getTableSQLError() const;

    /// @}

    /**
     * @addtogroup SetterGroup
     * @{
     */

    /**
     * @brief Sets the name of the database table.
     * @param newTableName The new table name.
     */
    void setTableName(const QString &newTableName);

    /**
     * @brief Sets the active database for the TableHandler.
     * @param newActiveDatabase The new active QSqlDatabase.
     */
    void setActiveDatabase(QSqlDatabase newActiveDatabase);

    /// @}

    /**
     * @brief Inserts values into the specified table.
     * @param tableName The name of the database table.
     * @param value1 The first value to insert.
     * @param value2 The second value to insert.
     * @param value3 The third value to insert.
     * @param value4 The fourth value to insert.
     * @param value5 The fifth value to insert.
     * @return True if the insertion is successful; otherwise, false.
     */
    bool insertIntoTable(const QString &tableName, const QString &value1, const QString &value2,
                         const QString &value3, const QString &value4, const QString &value5);



    const QString &getActiveTableName() const;

    void setActiveTableName(const QString &newActiveTableName);

    const QSqlDatabase &getTblActiveDatabase() const;

    const QSqlError &getLastTableError() const;

private:

    QString activeTableName = "userTable"; ///< The name of the database table.

    QSqlTableModel *tableModel; ///< The QSqlTableModel associated with the TableHandler.

    QSqlDatabase tblActiveDatabase;

    QSqlError lastTableError;
};

/** @} */ // end of TableHandlerGroup
