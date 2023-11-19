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
    LauncherWindow::LauncherWindow(QWidget *parent, QSharedPointer<AposBackend::ObjectHandler> newObjectHandler) :
            QMainWindow(parent),
            ui(new Ui::LauncherWindow) {
        ui->setupUi(this);
        objectHandler = std::move(newObjectHandler);
        //TODO: implement Logger
        launcherConnectUi();
    }
    //----------------------------------------------------------------------------------------------------------------//
    LauncherWindow::~LauncherWindow() {
        delete ui;
    }
    //----------------------------------------------------------------------------------------------------------------//
    bool LauncherWindow::launcherConnectUi(){
        //TODO: implement Logger
        connect(ui->inShowDev, SIGNAL(clicked()), this, SLOT(showDevClicked()));
        //TODO: implement Logger
        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(pushButtonClicked()));
        return true;
    }
    //----------------------------------------------------------------------------------------------------------------//
    void LauncherWindow::showDevClicked() {
        emit openDevWindow();
    }
    //----------------------------------------------------------------------------------------------------------------//
    void LauncherWindow::pushButtonClicked() {
        emit openSettings();
    }
    //----------------------------------------------------------------------------------------------------------------//
    void LauncherWindow::retranslateUi() {
    }
}
