/**
 * @file windowhandler.cpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Source file for the WindowHandler class.
 *
 * @details This file contains the implementation of the WindowHandler class, which is a part of the application's frontend logic.
 * The WindowHandler class provides the functionality for managing the application's windows, including the launcher window, developer window, and settings window.
 * It interacts with the LauncherWindow, DevWindow, and SettingsWindow classes and uses the ObjectHandler class to manage the application's objects.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see AposBackend::ObjectHandler
 * @see LauncherWindow
 * @see DevWindow
 * @see SettingsWindow
 * @see QSharedPointer
 * @see QObject
 */
#include "windowhandler.hpp"

#include <utility>
#include "translatablewindow.hpp"

namespace AposFrontend {
    WindowHandler::WindowHandler(QSharedPointer<AposBackend::ObjectHandler> newObjectHandler,
                                 QSharedPointer<AposLogger::Logger> newLogger)
            : ptrObjectHandler(qMove(newObjectHandler)), ptrLogger(qMove(newLogger)) {

        ptrLauncherWindow = QSharedPointer<LauncherWindow>(new LauncherWindow(nullptr, ptrObjectHandler, ptrLogger));
        ptrSettingsWindow = QSharedPointer<SettingsWindow>(new SettingsWindow(nullptr, ptrObjectHandler, ptrLogger));
        (void) QObject::connect(ptrLauncherWindow.data(), &LauncherWindow::openDevWindow, this,
                                &WindowHandler::showDevWindow,
                                Qt::DirectConnection);
        (void) QObject::connect(ptrLauncherWindow.data(), &LauncherWindow::openSettings, this,
                                &WindowHandler::showSettingsWindow);
        (void) QObject::connect(ptrSettingsWindow.data(), &SettingsWindow::appliedSettings, this,
                                &WindowHandler::applySettings);
        ptrLogger->log("init", "WindowHandler initialized");
    }

    void WindowHandler::showLaunchWindow() {
        if (ptrDevWindow != nullptr) {
            if (!ptrDevWindow->isHidden()) {
                ptrDevWindow->hide();
                ptrLogger->log("status", "DevWindow hidden");
            }
        }
        ptrLauncherWindow->show();

        ptrLogger->log("status", "LauncherWindow shown");
    }

    void WindowHandler::showDevWindow() {
        ptrLauncherWindow->hide();
        ptrLogger->log("status", "LauncherWindow hidden");

        if (ptrDevWindow == nullptr) {
            ptrLogger->log("init", "DevWindow initializing");
            ptrDevWindow = QSharedPointer<DevWindow>(new DevWindow(nullptr, ptrObjectHandler, ptrLogger));
            QObject::connect(ptrDevWindow.data(), &DevWindow::returnToLauncher, this, &WindowHandler::showLaunchWindow,
                             Qt::DirectConnection);
            QObject::connect(ptrDevWindow.data(), &DevWindow::openSettings, this, &WindowHandler::showSettingsWindow,
                             Qt::DirectConnection);
        }
        if (ptrDevWindow != nullptr) {
            ptrDevWindow->show();
            ptrLogger->log("status", "DevWindow shown");
        }

    }

    void WindowHandler::showSettingsWindow() {
        ptrSettingsWindow->show();
        ptrLogger->log("status", "SettingsWindow shown");
    }

    void WindowHandler::applySettings() {
        ptrLogger->log("signal", "Applying settings");
        changeLanguages();
    }

    void WindowHandler::changeLanguages() {
        QWidgetList openWindows = ptrObjectHandler->getPtrApplication()->topLevelWidgets();
        for (QWidget *widget: std::as_const(openWindows)) {
            auto *tw = dynamic_cast<TranslatableWindow *>(widget);
            if (tw != nullptr) {
                tw->retranslateUi();
                ptrLogger->log("status", "Window retranslated");
            }
        }
    }

    void WindowHandler::handleAboutToQuit() {

        if (ptrDevWindow != nullptr) {
            ptrDevWindow->close();
            ptrLogger->log("closing", "DevWindow closed");
        }
        ptrSettingsWindow->close();
        ptrLogger->log("closing", "SettingsWindow closed");
        ptrLauncherWindow->close();
        ptrLogger->log("closing", "LauncherWindow closed");
        ptrLogger->log("closing", "Application quit");
        ptrLogger->log("closing", "Application is about to quit");
    }
}
