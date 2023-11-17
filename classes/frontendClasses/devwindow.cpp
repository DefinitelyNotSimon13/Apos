/**
 * @file DevWindow.cpp
 * @brief Implementation file for the DevWindow class.
 * @date 13.11.2023
 * @version 1.1.1
 * @author Simon Blum
 */

#include "devwindow.hpp"
#include "ui_devwindow.h"



DevWindow::DevWindow(QWidget *parent, ObjectHandler *newObjectHandler)
    : QMainWindow(parent)
    , ui(new Ui::DevWindow)
{
    ui->setupUi(this);
    objectHandler = newObjectHandler;
}

DevWindow::~DevWindow()
{
    delete ui;
}

void DevWindow::logEvent(QString type, QString message)
{
    ui->outLog->append("Log |  " +  type + ": " + message);
    qDebug() << "Logged:  " + type + " - " + message;
}

void DevWindow::logEvent(QString message, QSqlError error)
{
    ui->outLog->append("Log | " + message + "-" + error.text());
    qDebug() << "Logged: " + message + " - " + error.text();
}

void DevWindow::logEvent(QString message)
{
    ui->outLog->append("Log | " + message);
    qDebug() << "Logged: " + message;
}

void DevWindow::enableButtons(bool databaseLoaded)
{
    ui->btnAdd->setEnabled(databaseLoaded);
    ui->btnCloseDB->setEnabled(databaseLoaded);
    ui->btnUpdate->setEnabled(databaseLoaded);
    ui->btnExecute->setEnabled(databaseLoaded);
    ui->btnSelectTable->setEnabled(databaseLoaded);
    ui->btnInitDB->setEnabled(!databaseLoaded);
    logEvent("action", "Buttons enabled/disabled");
}

void DevWindow::setModelViews(QSqlTableModel &m)
{
    ui->outTable->setModel(&m);
    ui->outColumn->setModel(&m);
    ui->outList->setModel(&m);
}

void DevWindow::setModelViews()
{
    ui->outTable->setModel(nullptr);
    ui->outColumn->setModel(nullptr);
    ui->outList->setModel(nullptr);
}

void DevWindow::assignInputs()
{
    input1 = ui->inInput1->text();
    input2 = ui->inInput2->text();
    input3 = ui->inInput3->text();
    input4 = ui->inInput4->text();
    input5 = ui->inInput5->text();
}

void DevWindow::initDatabase(ObjectHandler *oH)
{
    if(!oH->initDatabaseObject()){
        logEvent("Error initiating database",  oH->getDbHandler()->getSqlError());
        return;
    }
    logEvent("action", "Database initiated");
    logEvent("action", QString(oH->getDbHandler()->getActiveDatabase().databaseName()) + " opened");
    logEvent("status", oH->getDbHandler()->getActiveDatabase().isOpen() ? "Database open" : "Database closed");
}

void DevWindow::closeDatabase(DatabaseHandler *db)
{
    db->closeDatabase();
    logEvent("action", "Database closed");
    logEvent("status", objectHandler->getDbHandler()->getActiveDatabase().isOpen() ? "Database open" : "Database closed");
}

bool DevWindow::checkCheckbox(int argCB)
{
    if(argCB == 2){
        return true;
    }
    else if (argCB == 0){
        return false;
    }
    else {
        logEvent("warning", "Something went wrong!");
        return false;
    }
}

void DevWindow::clearInputs(bool clearBool)
{
    if(clearBool){
        ui->inInput1->clear();
        ui->inInput2->clear();
        ui->inInput3->clear();
        ui->inInput4->clear();
        ui->inInput5->clear();
        logEvent("action", "cleared inputs");
    }
}

void DevWindow::clearCommandBox(bool clearBool)
{
   if(clearBool){
        ui->inCommand->clear();
        logEvent("action", "tried to clear command-line");
    }
}

void DevWindow::on_btnInitDB_clicked()
{
    initDatabase(objectHandler);
    qDebug() << "Database initialized";
    objectHandler->initTableObject(objectHandler->getActiveDatabase(), "userTable");
    qDebug() << "TableHander initialized";
    setModelViews(*objectHandler->getTableHandler()->getTableModel());
    qDebug() << "ModelViews set";
    enableButtons(true);
}

void DevWindow::on_btnCloseDB_clicked()
{
    setModelViews();
    closeDatabase(objectHandler->getDbHandler());
    enableButtons(false);
}

void DevWindow::on_btnExecute_clicked()
{
    if(!objectHandler->getDbHandler()->executeCommand(ui->inCommand->toPlainText())){
            logEvent("Error executing command", objectHandler->getDbHandler()->getSqlError());
    clearCommandBox(clearCommand);
    return;
}
clearCommandBox(clearCommand);
logEvent("action", "Command executed");
}

void DevWindow::on_btnSelectTable_clicked()
{
    objectHandler->getTableHandler()->generateTableModel();
    logEvent("action", "Table selected");
    setModelViews(*objectHandler->getTableHandler()->getTableModel());
}

void DevWindow::on_btnAdd_clicked()
{
    assignInputs();
    if(!objectHandler->getTableHandler()->insertIntoTable(objectHandler->getActiveTableName(), input1, input2, input3, input4, input5)){
        logEvent("Insert Error", objectHandler->getTableSqlError());
        clearInputs(clearInput);
        return;
    }
    clearInputs(clearInput);
    logEvent("action", "Values inserted");
}

void DevWindow::on_btnUpdate_clicked()
{
    // Generating table model before updating the views
    objectHandler->getTableHandler()->generateTableModel();
    setModelViews(*objectHandler->getTableHandler()->getTableModel());
    logEvent("action", "Table view updated");
}

void DevWindow::on_clearCommandAfterExecute_stateChanged(int arg1)
{
    clearCommand = checkCheckbox(arg1);
    logEvent("status","Command will clear after execute: " + QString(clearCommand ? "true" : "false"));
}

void DevWindow::on_clearInputsAfterInsert_stateChanged(int arg1)
{
    clearInput = checkCheckbox(arg1);
    logEvent("status","Inputs will be cleared after execution: " + QString(clearInput ? "true" : "false"));
}

void DevWindow::on_inReturnToLauncher_clicked()
{
    emit returnToLauncher();
}

void DevWindow::retranslateUi()
{
    ui->retranslateUi(this);
}

void DevWindow::on_inSettings_clicked()
{
    emit openSettings();
}

