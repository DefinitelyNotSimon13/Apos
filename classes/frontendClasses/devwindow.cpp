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
    DevWindow::DevWindow(QWidget *parent,
                         QSharedPointer<AposBackend::ObjectHandler> newObjectHandler,
                         QSharedPointer<AposLogger::Logger> newLogger) :
            QMainWindow(parent),
            ui(new Ui::DevWindow),
            ptrObjectHandler(qMove(newObjectHandler)),
            ptrLogger(qMove(newLogger)) {
        ui->setupUi(this);
        qDebug() << "DevWindow ui setup";
        qDebug() << "DevWindow ptrObjectHandler moved";

        devConnectUi();
        ptrLogger->log("init", "Slots and signals connected");
        ptrLogger->log("init", "DevWindow initialized");


    }

    //----------------------------------------------------------------------------------------------------------------//
    DevWindow::~DevWindow() {
        delete ui;
        ptrLogger->log("status", "DevWindow destroyed");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::devConnectUi() {
        //Buttons
        connect(ui->btnInitDB, &QPushButton::clicked, this, &DevWindow::initDbClicked);
        connect(ui->btnCloseDB, &QPushButton::clicked, this, &DevWindow::closeDbClicked);
        connect(ui->btnExecute, &QPushButton::clicked, this, &DevWindow::executeClicked);
        connect(ui->btnSelectTable, &QPushButton::clicked, this, &DevWindow::selectTableClicked);
        connect(ui->btnAdd, &QPushButton::clicked, this, &DevWindow::addValuesClicked);
        connect(ui->btnUpdate, &QPushButton::clicked, this, &DevWindow::updateTableClicked);
        connect(ui->inReturnToLauncher, &QPushButton::clicked, this, &DevWindow::returnToLauncherClicked);
        connect(ui->inSettings, &QPushButton::clicked, this, &DevWindow::settingsClicked);
        //Checkboxes
        connect(ui->clearCommandAfterExecute, &QCheckBox::stateChanged, this,
                &DevWindow::clearCommandAfterExecuteStateChanged);
        connect(ui->clearInputsAfterInsert, &QCheckBox::stateChanged, this,
                &DevWindow::clearInputsAfterInsertStateChanged);
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::logEvent(const QString &type, const QString &message) {
        ui->outLog->append("Log |  " + type + ": " + message);
        ptrLogger->log(type, message);
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::logEvent(const QString &message, const QSqlError &error) {
        ui->outLog->append("Log | " + message + "-" + error.text());
        ptrLogger->log("status", message + error.text());
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::logEvent(const QString &message) {
        ui->outLog->append("Log | " + message);
        ptrLogger->log("status", message);
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::enableButtons(bool databaseLoaded) {
        ui->btnAdd->setEnabled(databaseLoaded);
        ui->btnCloseDB->setEnabled(databaseLoaded);
        ui->btnUpdate->setEnabled(databaseLoaded);
        ui->btnExecute->setEnabled(databaseLoaded);
        ui->btnSelectTable->setEnabled(databaseLoaded);
        ui->btnInitDB->setEnabled(!databaseLoaded);
        logEvent("action", "Buttons enabled/disabled");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::setModelViews(const QSharedPointer<QSqlTableModel> &tableModel) {
        ui->outTable->setModel(tableModel.data());
        ui->outColumn->setModel(tableModel.data());
        ui->outList->setModel(tableModel.data());
        logEvent("action", "ModelViews set");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::setModelViews() {
        ui->outTable->setModel(nullptr);
        ui->outColumn->setModel(nullptr);
        ui->outList->setModel(nullptr);
        logEvent("action", "ModelViews cleared");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::assignInputs() {
        input1 = ui->inInput1->text();
        input2 = ui->inInput2->text();
        input3 = ui->inInput3->text();
        input4 = ui->inInput4->text();
        input5 = ui->inInput5->text();
        ptrLogger->log("status", "Inputs assigned");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::initDatabase() {
        if (!ptrObjectHandler->initDatabaseObject()) {
            logEvent("Error initiating database", ptrObjectHandler->getPtrDbHandler()->getSqlError());
        } else {
            logEvent("action", "Database initiated");
            logEvent("action",
                     QString(ptrObjectHandler->getPtrDbHandler()->getActiveDatabase()->databaseName()) + " opened");
            logEvent("status", ptrObjectHandler->getPtrDbHandler()->getActiveDatabase()->isOpen()
                               ? "Database open" : "Database closed");
        }
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::closeDatabase(const QSharedPointer<AposDatabase::DatabaseHandler> &db) {
        db->closeDatabase();
        logEvent("action", "Database closed");
        logEvent("status",
                 ptrObjectHandler->getPtrDbHandler()->getActiveDatabase()->isOpen() ? "Database open"
                                                                                    : "Database closed");
    }

    //----------------------------------------------------------------------------------------------------------------//
    bool DevWindow::checkCheckbox(int argCb) {
        bool checked = false;
        if (argCb == 2) {
            checked = true;
        } else if (argCb == 0) {
            checked = false;
        } else {
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
            logEvent("action", "cleared inputs");
        }
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::clearCommandBox(bool clearBool) {
        if (clearBool) {
            ui->inCommand->clear();
            logEvent("action", "tried to clear command-line");
        }
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::initDbClicked() {
        //! @BUG: When reopening the database crashes the application
        initDatabase();
        if (!ptrObjectHandler->initTableObject("userTable")) {
            logEvent("Error initiating table", ptrObjectHandler->getTableSqlError());
            return;
        }
        enableButtons(true);
        ptrLogger->log("status", "Database initiated");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::closeDbClicked() {
        setModelViews();
        closeDatabase(ptrObjectHandler->getPtrDbHandler());
        enableButtons(false);
        ptrLogger->log("status", "Database closed");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::executeClicked() {
        if (!ptrObjectHandler->getPtrDbHandler()->executeCommand(ui->inCommand->toPlainText())) {
            logEvent("Error executing command", ptrObjectHandler->getPtrDbHandler()->getSqlError());
            clearCommandBox(clearCommand);
            return;
        }
        clearCommandBox(clearCommand);
        logEvent("action", "Command executed");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::selectTableClicked() {
        ptrObjectHandler->getPtrTableHandler()->generateTableModel();
        logEvent("action", "Table selected");
        setModelViews(ptrObjectHandler->getPtrTableHandler()->getTableModel());
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::addValuesClicked() {
        assignInputs();
        if (!ptrObjectHandler->getPtrTableHandler()->insertIntoTable(ptrObjectHandler->getActiveTableName(), input1,
                                                                     input2,
                                                                     input3,
                                                                     input4, input5)) {
            logEvent("Insert Error", ptrObjectHandler->getTableSqlError());
            clearInputs(clearInput);
            return;
        }
        clearInputs(clearInput);
        logEvent("action", "Values inserted");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::updateTableClicked() {
        ptrObjectHandler->getPtrTableHandler()->generateTableModel();
        setModelViews(ptrObjectHandler->getPtrTableHandler()->getTableModel());
        logEvent("action", "Table view updated");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::clearCommandAfterExecuteStateChanged(int arg1) {
        clearCommand = checkCheckbox(arg1);
        logEvent("status", "Command will clear after execute: " + QString(clearCommand ? "true" : "false"));
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::clearInputsAfterInsertStateChanged(int arg1) {
        clearInput = checkCheckbox(arg1);
        logEvent("status", "Inputs will be cleared after execution: " + QString(clearInput ? "true" : "false"));
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::returnToLauncherClicked() {
        ptrLogger->log("signal", "Return to launcher requested");
        emit returnToLauncher();
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::settingsClicked() {
        ptrLogger->log("signal", "Open settings requested");
        emit openSettings();
    }

    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::retranslateUi() {
        ui->retranslateUi(this);
        ptrLogger->log("status", "DevWindow retranslated");
    }
}
