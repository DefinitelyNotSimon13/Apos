#pragma once

#include <QDebug>
#include <QtSql>


class DatabaseHandler
{
public:


    DatabaseHandler();


    bool initDatabase();


    void closeDatabase();


    bool executeCommand(QString command);

    const QSqlDatabase &getActiveDatabase() const;


    const QSqlError &getSqlError() const;


    void setDatabasePath(const QString &newDatabasePath);



    void setLastSqlError(const QSqlError &newLastSqlError);

private:

    QSqlError lastSqlError;

    QSqlDatabase activeDatabase;

    QString databasePath = R"(C:\Users\Clean\Documents\Projekte\Apos-DatabaseManager\Project\resources\defaultDatabase\userDatabase.db)";

};
