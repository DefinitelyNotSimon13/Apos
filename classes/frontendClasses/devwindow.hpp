// Copyright (c) 2023. LGPL-V3
//

#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QtSql>

#include "../backendClasses/objecthandler.hpp"
#include "translatablewindow.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class DevWindow; }
QT_END_NAMESPACE

class DevWindow : public QMainWindow, public TranslatableWindow {
Q_OBJECT

public:

    DevWindow(QWidget *parent = nullptr, ObjectHandler *objectHandler = nullptr);


    ~DevWindow();

    void logEvent(QString type, QString message);

    void logEvent(QString message, QSqlError error);


    void logEvent(QString message);

    void retranslateUi();


signals:

    void returnToLauncher();

    void openSettings();

private slots:


    void on_btnInitDB_clicked();


    void on_btnCloseDB_clicked();


    void on_btnExecute_clicked();


    void on_btnSelectTable_clicked();


    void on_btnAdd_clicked();


    void on_btnUpdate_clicked();

    void on_clearCommandAfterExecute_stateChanged(int arg1);


    void on_clearInputsAfterInsert_stateChanged(int arg1);


    void on_inReturnToLauncher_clicked();

    void on_inSettings_clicked();

private:


    void enableButtons(bool databaseLoaded);


    void setModelViews(QSqlTableModel &m);

    void setModelViews();

    void assignInputs();


    bool checkCheckbox(int argCB);

    void initDatabase(ObjectHandler *oH);

    void closeDatabase(DatabaseHandler *db);

    void clearInputs(bool clearBool);


    void clearCommandBox(bool clearBool);

    Ui::DevWindow *ui;
    ObjectHandler *objectHandler;

    QString input1, input2, input3, input4, input5;
    bool clearCommand = false, clearInput = false;
};


