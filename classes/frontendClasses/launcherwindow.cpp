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
    }
    //----------------------------------------------------------------------------------------------------------------//
    LauncherWindow::~LauncherWindow() {
        delete ui;
    }
    //----------------------------------------------------------------------------------------------------------------//
    void LauncherWindow::on_inShowDev_clicked() {
        emit openDevWindow();
    }
    //----------------------------------------------------------------------------------------------------------------//
    void LauncherWindow::on_pushButton_clicked() {
        emit openSettings();
    }
    //----------------------------------------------------------------------------------------------------------------//
    void LauncherWindow::retranslateUi() {
    }
}
