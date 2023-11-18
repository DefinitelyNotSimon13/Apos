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
        ui->setupUi(this);
        ptrObjectHandler = std::move(newObjectHandler);
    }
    //----------------------------------------------------------------------------------------------------------------//
    DevWindow::~DevWindow() {
        delete ui;
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::logEvent(const QString &type,const QString &message) {
        ui->outLog->append("Log |  " + type + ": " + message);
        qDebug() << "Logged:  " + type + " - " + message;
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::logEvent(const QString &message,const QSqlError &error) {
        ui->outLog->append("Log | " + message + "-" + error.text());
        qDebug() << "Logged: " + message + " - " + error.text();
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::logEvent(const QString &message) {
        ui->outLog->append("Log | " + message);
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
        logEvent("action", "Buttons enabled/disabled");
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::setModelViews(const QSharedPointer<QSqlTableModel>& tableModel) {
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
            logEvent("Error initiating database", ptrObjectHandler->getPtrDbHandler()->getSqlError());

        }
        else {
            logEvent("action", "Database initiated");
            logEvent("action",
                     QString(ptrObjectHandler->getPtrDbHandler()->getActiveDatabase()->databaseName()) + " opened");
            logEvent("status", ptrObjectHandler->getPtrDbHandler()->getActiveDatabase()->isOpen()
                                                                                ? "Database open": "Database closed");
        }
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::closeDatabase(const QSharedPointer<AposDatabase::DatabaseHandler>& db) {
        db->closeDatabase();
        logEvent("action", "Database closed");
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
    void DevWindow::on_btnInitDB_clicked() {
        initDatabase();
        qDebug() << "Database initialized";
        if(!ptrObjectHandler->initTableObject("userTable")){
            logEvent("Error initiating table", ptrObjectHandler->getTableSqlError());
            return;
        }
        qDebug() << "TableHander initialized";
        setModelViews(ptrObjectHandler->getPtrTableHandler()->getTableModel());
        qDebug() << "ModelViews set";
        enableButtons(true);
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::on_btnCloseDB_clicked() {
        setModelViews();
        closeDatabase(ptrObjectHandler->getPtrDbHandler());
        enableButtons(false);
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::on_btnExecute_clicked() {
        if (!ptrObjectHandler->getPtrDbHandler()->executeCommand(ui->inCommand->toPlainText())) {
            logEvent("Error executing command", ptrObjectHandler->getPtrDbHandler()->getSqlError());
            clearCommandBox(clearCommand);
            return;
        }
        clearCommandBox(clearCommand);
        logEvent("action", "Command executed");
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::on_btnSelectTable_clicked() {
        ptrObjectHandler->getPtrTableHandler()->generateTableModel();
        logEvent("action", "Table selected");
        setModelViews(ptrObjectHandler->getPtrTableHandler()->getTableModel());
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::on_btnAdd_clicked() {
        assignInputs();
        if (!ptrObjectHandler->getPtrTableHandler()->insertIntoTable(ptrObjectHandler->getActiveTableName(), input1, input2,
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
    void DevWindow::on_btnUpdate_clicked() {
        ptrObjectHandler->getPtrTableHandler()->generateTableModel();
        setModelViews(ptrObjectHandler->getPtrTableHandler()->getTableModel());
        logEvent("action", "Table view updated");
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::on_clearCommandAfterExecute_stateChanged(int arg1) {
        clearCommand = checkCheckbox(arg1);
        logEvent("status", "Command will clear after execute: " + QString(clearCommand ? "true" : "false"));
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::on_clearInputsAfterInsert_stateChanged(int arg1) {
        clearInput = checkCheckbox(arg1);
        logEvent("status", "Inputs will be cleared after execution: " + QString(clearInput ? "true" : "false"));
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::on_inReturnToLauncher_clicked() {
        emit returnToLauncher();
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::retranslateUi() {
        ui->retranslateUi(this);
    }
    //----------------------------------------------------------------------------------------------------------------//
    void DevWindow::on_inSettings_clicked() {
        emit openSettings();
    }
}
