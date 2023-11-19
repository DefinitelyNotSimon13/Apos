/**
 * @file windowhandler.hpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Header file for the WindowHandler class.
 *
 * @details This file contains the declaration of the WindowHandler class, which is a part of the application's frontend logic.
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

#pragma once

#include <QObject>
#include "launcherwindow.hpp"
#include "devwindow.hpp"
#include "settingswindow.hpp"
#include "../backendClasses/objecthandler.hpp"
#include "../backendClasses/logger.hpp"

//--------------------------------------------------------------------------------------------------------------------//
namespace AposFrontend {
    /**
     * @class WindowHandler
     * @ingroup Ui-Functions
     * @brief Provides the functionality for managing the application's windows.
     * @details The WindowHandler class is a part of the application's frontend logic.
     * It provides the functionality for showing the launcher window, developer window, and settings window.
     * It also applies settings and changes languages.
     *
     * @see AposBackend::ObjectHandler
     * @see LauncherWindow
     * @see DevWindow
     * @see SettingsWindow
     * @see QSharedPointer
     * @see QObject
     */
    class WindowHandler : public QObject {
    public:
        /**
         * @brief Constructor for the WindowHandler class.
         * @ingroup Constructructors-Destructors
         * @details This constructor initializes the WindowHandler object with an ObjectHandler object.
         * @param newObjectHandler Shared pointer to the ObjectHandler object.
         */
        explicit WindowHandler(QSharedPointer<AposBackend::ObjectHandler> newObjectHandler,
                               QSharedPointer<AposLogger::Logger> newLogger);

        /**
         * @brief Shows the launcher window.
         * @ingroup Ui-Functions
         * @details This function shows the launcher window of the application.
         */
        void showLaunchWindow();


    public slots:

        void handleAboutToQuit();

    private slots:

        /**
         * @brief Shows the developer window.
         * @ingroup Ui-Functions
         * @details This slot is triggered when the user wants to open the developer window.
         */
        void showDevWindow();

        /**
         * @brief Shows the settings window.
         * @ingroup Ui-Functions
         * @details This slot is triggered when the user wants to open the settings window.
         */
        void showSettingsWindow();

        /**
         * @brief Applies settings.
         * @ingroup Ui-Functions
         * @details This slot is triggered when the user applies the settings.
         */
        void applySettings();

    private:
        /**
         * @brief Changes languages.
         * @ingroup Ui-Functions
         * @details This function changes the language of the application's user interface.
         */
        void changeLanguages();

        /**
         * @brief Shared pointer to the LauncherWindow object.
         * @ingroup Variables
         * @details This shared pointer is used to access the LauncherWindow object.
         */
        QSharedPointer<LauncherWindow> ptrLauncherWindow;

        /**
         * @brief Shared pointer to the DevWindow object.
         * @ingroup Variables
         * @details This shared pointer is used to access the DevWindow object.
         */
        QSharedPointer<DevWindow> ptrDevWindow;

        /**
         * @brief Shared pointer to the SettingsWindow object.
         * @ingroup Variables
         * @details This shared pointer is used to access the SettingsWindow object.
         */
        QSharedPointer<SettingsWindow> ptrSettingsWindow;

        /**
         * @brief Shared pointer to the ObjectHandler object.
         * @ingroup Variables
         * @details This shared pointer is used to access the ObjectHandler object.
         */
        QSharedPointer<AposBackend::ObjectHandler> ptrObjectHandler;

        /**
         * @brief Shared pointer to the Logger object.
         * @ingroup Variables
         * @details This shared pointer is used to access the Logger object.
         */
        QSharedPointer<AposLogger::Logger> ptrLogger;
    };
}