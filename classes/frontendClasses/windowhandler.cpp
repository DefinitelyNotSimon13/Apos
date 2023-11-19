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
    WindowHandler::WindowHandler(QSharedPointer<AposBackend::ObjectHandler> newObjectHandler) {

        ptrObjectHandler = qMove(newObjectHandler);
        ptrLauncherWindow = QSharedPointer<LauncherWindow>(new LauncherWindow(nullptr, ptrObjectHandler));
        ptrSettingsWindow = QSharedPointer<SettingsWindow>(new SettingsWindow(nullptr, ptrObjectHandler));
        (void)QObject::connect(ptrLauncherWindow.data(), &LauncherWindow::openDevWindow, this, &WindowHandler::showDevWindow,
                         Qt::DirectConnection);
        (void)QObject::connect(ptrLauncherWindow.data(), &LauncherWindow::openSettings, this, &WindowHandler::showSettingsWindow);
        (void)QObject::connect(ptrSettingsWindow.data(), &SettingsWindow::appliedSettings, this, &WindowHandler::applySettings);

    }

    void WindowHandler::showLaunchWindow() {
        if (ptrDevWindow != nullptr) {
            if (!ptrDevWindow->isHidden()) {
                ptrDevWindow->hide();
            }
        }
        ptrLauncherWindow->show();
    }

    void WindowHandler::showDevWindow() {
        ptrLauncherWindow->hide();
        if (ptrDevWindow == nullptr) {
            ptrDevWindow = QSharedPointer<DevWindow>(new DevWindow(nullptr, ptrObjectHandler));
            QObject::connect(ptrDevWindow.data(), &DevWindow::returnToLauncher, this, &WindowHandler::showLaunchWindow,
                             Qt::DirectConnection);
            QObject::connect(ptrDevWindow.data(), &DevWindow::openSettings, this, &WindowHandler::showSettingsWindow,
                             Qt::DirectConnection);
        }
        if(ptrDevWindow != nullptr){
            ptrDevWindow->show();
        }

    }

    void WindowHandler::showSettingsWindow() {
        ptrSettingsWindow->show();
    }

    void WindowHandler::applySettings() {
        changeLanguages();
    }

    void WindowHandler::changeLanguages() {
        QWidgetList openWindows = ptrObjectHandler->getPtrApplication()->topLevelWidgets();
        for (QWidget* widget: std::as_const(openWindows)) {
            auto *tw = dynamic_cast<TranslatableWindow *>(widget);
            if (tw != nullptr) {
                qDebug() << "Dynamic cast pointer adress " << tw;
                tw->retranslateUi();
            }
        }
        qDebug() << openWindows;
    }
}
