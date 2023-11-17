#pragma once

#include <QDebug>
#include <QtSql>


class TableHandler
{
public:


    TableHandler();


    TableHandler(const QSqlDatabase& newActiveDatabase, const QString& tableName);


    void generateTableModel();


    void generateTableModel(QSqlDatabase& activeDatabase, const QString &tableName);


    QSqlTableModel *getTableModel() const;




    const QSqlError &getTableSQLError() const;


    void setTableName(const QString &newTableName);


    void setActiveDatabase(QSqlDatabase newActiveDatabase);


    bool insertIntoTable(const QString &tableName, const QString &value1, const QString &value2,
                         const QString &value3, const QString &value4, const QString &value5);



    const QString &getActiveTableName() const;

    void setActiveTableName(const QString &newActiveTableName);

    const QSqlDatabase &getTblActiveDatabase() const;

    const QSqlError &getLastTableError() const;

private:

    QString activeTableName = "userTable";

    QSqlTableModel *tableModel;

    QSqlDatabase tblActiveDatabase;

    QSqlError lastTableError;
};


