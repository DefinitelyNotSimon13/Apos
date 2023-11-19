/**
 * @file devwindow.cpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Source file for the DevWindow class.
 *
 * @details This file contains the implementation of the DevWindow class, which is a part of the application's frontend logic.
 * The DevWindow class inherits from QMainWindow and TranslatableWindow, and it provides the user interface for the developer window.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see QMainWindow
 * @see TranslatableWindow
 * @see AposBackend::ObjectHandler
 */
#include "devwindow.hpp"
#include "ui_devwindow.h"

namespace AposFrontend {
    //----------------------------------------------------------------------------------------------------------------//
    DevWindow::DevWindow(QWidget *parent, QSharedPointer<AposBackend::ObjectHandler> newObjectHandler)
            : QMainWindow(parent), ui(new Ui::DevWindow) {
        qDebug() << "DevWindow constructor called";
        ui->setupUi(this);
        qDebug() << "DevWindow ui setup";
        ptrObjectHandler = qMove(newObjectHandler);
        qDebug() << "DevWindow ptrObjectHandler moved";
        //TODO: implement Logger
        devConnectUi();
        qDebug() << "DevWindow connected UiElements";





    }
    //----------------------------------------------------------------------------------------------------------------//
    DevWindow::~DevWindow() {
        delete ui;
    }
    //----------------------------------------------------------------------------------------------------------------//
    bool DevWindow::devConnectUi() {
        //TODO: implement Logger
        //Buttons
        connect(ui->btnInitDB, &QPushButton::clicked, this, &DevWindow::initDbClicked);
        connect(ui->btnCloseDB, &QPushButton::clicked, this, &DevWindow::closeDBClicked);
        connect(ui->btnExecute, &QPushButton::clicked, this, &DevWindow::executeClicked);
        connect(ui->btnSelectTable, &QPushButton::clicked, this, &DevWindow::selectTableClicked);
        connect(ui->btnAdd, &QPushButton::clicked, this, &DevWindow::addValuesClicked);
        connect(ui->btnUpdate, &QPushButton::clicked, this, &DevWindow::updateTableClicked);
        connect(ui->inReturnToLauncher, &QPushButton::clicked, this, &DevWindow::returnToLauncherClicked);
        connect(ui->inSettings, &QPushButton::clicked, this, &DevWindow::settingsClicked);
        //Checkboxes
        connect(ui->clearCommandAfterExecute, &QCheckBox::stateChanged, this, &DevWindow::clearCommandAfterExecuteStateChanged);
        connect(ui->clearInputsAfterInsert, &QCheckBox::stateChanged, this, &DevWindow::clearInputsAfterInsertStateChanged);
        return true;
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::logEvent(const QString &type,const QString &message) {
        //TODO: implement Logger
        ui->outLog->append("Log |  " + type + ": " + message);
        //TODO: implement Logger
        qDebug() << "Logged:  " + type + " - " + message;
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::logEvent(const QString &message,const QSqlError &error) {
        //TODO: implement Logger
        ui->outLog->append("Log | " + message + "-" + error.text());
        //TODO: implement Logger
        qDebug() << "Logged: " + message + " - " + error.text();
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::logEvent(const QString &message) {
        //TODO: implement Logger
        ui->outLog->append("Log | " + message);
        //TODO: implement Logger
        qDebug() << "Logged: " + message;
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::enableButtons(bool databaseLoaded) {
        ui->btnAdd->setEnabled(databaseLoaded);
        ui->btnCloseDB->setEnabled(databaseLoaded);
        ui->btnUpdate->setEnabled(databaseLoaded);
        ui->btnExecute->setEnabled(databaseLoaded);
        ui->btnSelectTable->setEnabled(databaseLoaded);
        ui->btnInitDB->setEnabled(!databaseLoaded);
        //TODO: implement Logger
        logEvent("action", "Buttons enabled/disabled");
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::setModelViews(const QSharedPointer<QSqlTableModel>& tableModel) {
        //TODO: implement Logger
        qDebug() <<"SharedPointer.data(): " << tableModel->database();
        ui->outTable->setModel(tableModel.data());
        ui->outColumn->setModel(tableModel.data());
        ui->outList->setModel(tableModel.data());
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::setModelViews() {
        ui->outTable->setModel(nullptr);
        ui->outColumn->setModel(nullptr);
        ui->outList->setModel(nullptr);
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::assignInputs() {
        input1 = ui->inInput1->text();
        input2 = ui->inInput2->text();
        input3 = ui->inInput3->text();
        input4 = ui->inInput4->text();
        input5 = ui->inInput5->text();
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::initDatabase() {
        if (!ptrObjectHandler->initDatabaseObject()) {
            //TODO: implement Logger
            logEvent("Error initiating database", ptrObjectHandler->getPtrDbHandler()->getSqlError());

        }
        else {
            //TODO: implement Logger
            logEvent("action", "Database initiated");
            //TODO: implement Logger
            logEvent("action",
                     QString(ptrObjectHandler->getPtrDbHandler()->getActiveDatabase()->databaseName()) + " opened");
            //TODO: implement Logger
            logEvent("status", ptrObjectHandler->getPtrDbHandler()->getActiveDatabase()->isOpen()
                                                                                ? "Database open": "Database closed");
        }
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::closeDatabase(const QSharedPointer<AposDatabase::DatabaseHandler>& db) {
        db->closeDatabase();
        //TODO: implement Logger
        logEvent("action", "Database closed");
        //TODO: implement Logger
        logEvent("status",
                 ptrObjectHandler->getPtrDbHandler()->getActiveDatabase()->isOpen() ? "Database open" : "Database closed");
    }
    //----------------------------------------------------------------------------------------------------------------//
    bool DevWindow::checkCheckbox(int argCb) {
        bool checked = false;
        if (argCb == 2) {
            checked = true;
        } else if (argCb == 0) {
            checked = false;
        } else {
            //TODO: implement Logger
            logEvent("warning", "Something went wrong!");
            checked = false;
        }
        return checked;
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::clearInputs(bool clearBool) {
        if (clearBool) {
            ui->inInput1->clear();
            ui->inInput2->clear();
            ui->inInput3->clear();
            ui->inInput4->clear();
            ui->inInput5->clear();
            //TODO: implement Logger
            logEvent("action", "cleared inputs");
        }
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::clearCommandBox(bool clearBool) {
        if (clearBool) {
            ui->inCommand->clear();
            //TODO: implement Logger
            logEvent("action", "tried to clear command-line");
        }
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::initDbClicked() {
        initDatabase();
        //TODO: implement Logger
        qDebug() << "Database initialized";
        if(!ptrObjectHandler->initTableObject("userTable")){
            //TODO: implement Logger
            logEvent("Error initiating table", ptrObjectHandler->getTableSqlError());
            return;
        }
        //TODO: implement Logger
        qDebug() << "TableHander initialized";
        setModelViews(ptrObjectHandler->getPtrTableHandler()->getTableModel());
        //TODO: implement Logger
        qDebug() << "ModelViews set";
        enableButtons(true);
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::closeDBClicked() {
        setModelViews();
        closeDatabase(ptrObjectHandler->getPtrDbHandler());
        enableButtons(false);
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::executeClicked() {
        if (!ptrObjectHandler->getPtrDbHandler()->executeCommand(ui->inCommand->toPlainText())) {
            //TODO: implement Logger
            logEvent("Error executing command", ptrObjectHandler->getPtrDbHandler()->getSqlError());
            clearCommandBox(clearCommand);
            return;
        }
        clearCommandBox(clearCommand);
        //TODO: implement Logger
        logEvent("action", "Command executed");
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::selectTableClicked() {
        ptrObjectHandler->getPtrTableHandler()->generateTableModel();
        //TODO: implement Logger
        logEvent("action", "Table selected");
        setModelViews(ptrObjectHandler->getPtrTableHandler()->getTableModel());
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::addValuesClicked() {
        assignInputs();
        if (!ptrObjectHandler->getPtrTableHandler()->insertIntoTable(ptrObjectHandler->getActiveTableName(), input1, input2,
                                                               input3,
                                                               input4, input5)) {
            //TODO: implement Logger
            logEvent("Insert Error", ptrObjectHandler->getTableSqlError());
            clearInputs(clearInput);
            return;
        }
        clearInputs(clearInput);
        //TODO: implement Logger
        logEvent("action", "Values inserted");
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::updateTableClicked() {
        ptrObjectHandler->getPtrTableHandler()->generateTableModel();
        setModelViews(ptrObjectHandler->getPtrTableHandler()->getTableModel());
        //TODO: implement Logger
        logEvent("action", "Table view updated");
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::clearCommandAfterExecuteStateChanged(int arg1) {
        clearCommand = checkCheckbox(arg1);
        //TODO: implement Logger
        logEvent("status", "Command will clear after execute: " + QString(clearCommand ? "true" : "false"));
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::clearInputsAfterInsertStateChanged(int arg1) {
        clearInput = checkCheckbox(arg1);
        //TODO: implement Logger
        logEvent("status", "Inputs will be cleared after execution: " + QString(clearInput ? "true" : "false"));
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::returnToLauncherClicked() {
        emit returnToLauncher();
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::settingsClicked() {
        emit openSettings();
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::retranslateUi() {
        ui->retranslateUi(this);
    }

}
