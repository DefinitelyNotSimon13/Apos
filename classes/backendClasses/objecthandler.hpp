// Copyright (c) 2023. LGPL-V3
//

#pragma once

#include <QApplication>
#include <QDebug>
#include <QtSql>

#include "../databaseClasses/databasehandler.hpp"
#include "../databaseClasses/tablehandler.hpp"

class ObjectHandler {
public:
    ObjectHandler(QApplication *newApplication, DatabaseHandler *newDBHandler, TableHandler *newTableHandler);

    void setActiveTableName(const QString &newActiveTableName);

    bool initDatabaseObject();

    bool initTableObject();

    bool initTableObject(QSqlDatabase inputActiveDatabase, const QString &inputTableName);

    const QSqlDatabase &getActiveDatabase() const;

    TableHandler *getTableHandler() const;

    DatabaseHandler *getDbHandler() const;

    const QString &getActiveTableName() const;

    const QSqlError &getTableSqlError() const;

    QApplication *application;
private:
    DatabaseHandler *dbHandler;
    TableHandler *tableHandler;
};


