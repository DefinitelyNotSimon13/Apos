/**
 * @file launcherwindow.hpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Header file for the LauncherWindow class.
 *
 * @details This file contains the declaration of the LauncherWindow class, which is a part of the application's frontend logic.
 * The LauncherWindow class inherits from QMainWindow and TranslatableWindow, and it provides the user interface for the launcher window.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see AposBackend::ObjectHandler
 * @see TranslatableWindow
 * @see QMainWindow
 */

#pragma once

#include <QMainWindow>

#include "../backendClasses/objecthandler.hpp"
#include "translatablewindow.hpp"
#include "../backendClasses/logger.hpp"

//--------------------------------------------------------------------------------------------------------------------//
namespace Ui {
    class LauncherWindow;
}
//--------------------------------------------------------------------------------------------------------------------//
namespace AposFrontend {
    /**
     * @class LauncherWindow
     * @ingroup Ui-Functions
     * @brief Provides the user interface for the launcher window.
     *
     * @details The LauncherWindow class provides the functionality for opening the developer window and settings.
     * It interacts with the QMainWindow and TranslatableWindow classes and uses the ObjectHandler class
     * to manage the application's objects.
     *
     * @see AposBackend::ObjectHandler
     * @see TranslatableWindow
     * @see QMainWindow
     */
    class LauncherWindow : public QMainWindow, public TranslatableWindow {
    Q_OBJECT

    public:
        /**
         * @brief Constructor for the LauncherWindow class.
         * @ingroup Constructructors-Destructors
         * @details This constructor initializes the LauncherWindow object with a parent widget and an ObjectHandler object.
         * @param parent Pointer to the parent widget.
         * @param newObjectHandler Shared pointer to the ObjectHandler object.
         */
        explicit LauncherWindow(QWidget *parent,
                                QSharedPointer<AposBackend::ObjectHandler> newObjectHandler,
                                QSharedPointer<AposLogger::Logger> newLogger);

        /**
         * @brief Destructor for the LauncherWindow class.
         * @ingroup Constructructors-Destructors
         * @details This destructor cleans up the LauncherWindow object.
         */
        ~LauncherWindow() override;;

        /**
         * @brief Retranslates the user interface.
         * @ingroup Ui-Functions
         * @details This function retranslates the user interface of the LauncherWindow object.
         */
        void retranslateUi() override;

    signals:

        /**
         * @brief Signal for opening the developer window.
         * @ingroup Signal-Funtions
         * @details This signal is emitted when the user wants to open the developer window.
         */
        void openDevWindow();

        /**
         * @brief Signal for opening the settings.
         * @ingroup Signal-Funtions
         * @details This signal is emitted when the user wants to open the settings.
         */
        void openSettings();

    private slots:

        /**
         * @brief Slot for the 'ShowDev' button click event.
         * @ingroup Slot-Functions
         * @details This slot is triggered when the 'ShowDev' button is clicked.
         */
        void showDevClicked();

        /**
         * @brief Slot for the 'PushButton' button click event.
         * @ingroup Slot-Functions
         * @details This slot is triggered when the 'PushButton' button is clicked.
         */
        void showSettingsClicked();

    private:
        /**
         * @brief Connects the user interface.
         * @ingroup Ui-Functions
         * @details This function connects the user interface of the LauncherWindow object.
         */
        void launcherConnectUi();

        /**
         * @brief Pointer to the user interface of the LauncherWindow object.
         * @ingroup Variables
         * @details This pointer is used to access the user interface of the LauncherWindow object.
         */
        Ui::LauncherWindow *ui;

        /**
         * @brief Shared pointer to the ObjectHandler object.
         * @ingroup Variables
         * @details This shared pointer is used to access the ObjectHandler object.
         */
        QSharedPointer<AposBackend::ObjectHandler> objectHandler = nullptr;

        /**
         * @brief Shared pointer to the Logger object.
         * @ingroup Variables
         * @details This shared pointer is used to access the Logger object.
         */
        QSharedPointer<AposLogger::Logger> ptrLogger = nullptr;
    };
}