/**
 * @file launcherwindow.cpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Source file for the LauncherWindow class.
 *
 * @details This file contains the implementation of the LauncherWindow class, which is a part of the application's frontend logic.
 * The LauncherWindow class inherits from QMainWindow and TranslatableWindow, and it provides the user interface for the launcher window.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see AposBackend::ObjectHandler
 * @see TranslatableWindow
 * @see QMainWindow
 */
#include "launcherwindow.hpp"

#include <utility>
#include "ui_launcherwindow.h"


namespace AposFrontend {
    //----------------------------------------------------------------------------------------------------------------//
    LauncherWindow::LauncherWindow(QWidget *parent, QSharedPointer<AposBackend::ObjectHandler> newObjectHandler,
                                   QSharedPointer<AposLogger::Logger> newLogger) :
            QMainWindow(parent),
            ui(new Ui::LauncherWindow),
            ptrLogger(qMove(newLogger)) {
        ui->setupUi(this);
        objectHandler = std::move(newObjectHandler);
        launcherConnectUi();
        ptrLogger->log("init", "LauncherWindow initialized");
    }

    //----------------------------------------------------------------------------------------------------------------//
    LauncherWindow::~LauncherWindow() {
        delete ui;
        ptrLogger->log("status", "LauncherWindow destroyed");
    }

    //----------------------------------------------------------------------------------------------------------------//
    void LauncherWindow::launcherConnectUi() {
        connect(ui->btnShowDev, SIGNAL(clicked()), this, SLOT(showDevClicked()));
        connect(ui->btnSettings, SIGNAL(clicked()), this, SLOT(showSettingsClicked()));
    }

    //----------------------------------------------------------------------------------------------------------------//
    void LauncherWindow::showDevClicked() {
        ptrLogger->log("signal", "Dev window requested");
        emit openDevWindow();
    }

    //----------------------------------------------------------------------------------------------------------------//
    void LauncherWindow::showSettingsClicked() {
        ptrLogger->log("signal", "Settings window requested");
        emit openSettings();
    }

    //----------------------------------------------------------------------------------------------------------------//
    void LauncherWindow::retranslateUi() {
        ui->retranslateUi(this);
        ptrLogger->log("status", "LauncherWindow retranslated");
    }
}
