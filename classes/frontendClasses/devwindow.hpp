/**
 * @file devwindow.hpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Header file for the DevWindow class.
 *
 * @details This file contains the declaration of the DevWindow class, which is a part of the application's frontend logic.
 * The DevWindow class inherits from QMainWindow and TranslatableWindow, and it provides the user interface for the developer window.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see TranslatableWindow
 * @see AposBackend::ObjectHandler
 * @see QMainWindow
 * @see QSharedPointer
 * @see QDebug
 * @see QtSql
 */

#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QtSql>

#include "../backendClasses/objecthandler.hpp"
#include "translatablewindow.hpp"
#include "../backendClasses/logger.hpp"

//--------------------------------------------------------------------------------------------------------------------//
namespace Ui { class DevWindow; }
//--------------------------------------------------------------------------------------------------------------------//
namespace AposFrontend {
    /**
     * @class DevWindow
     *
     * @brief Provides the user interface for the developer window.
     *
     * @details
     * The DevWindow class provides the functionality for logging events, retranslating the user interface,
     * initializing and closing the database, setting model views, enabling buttons, assigning inputs, checking checkboxes,
     * and clearing inputs and the command box.
     *
     * @see QMainWindow
     * @see TranslatableWindow
     * @see AposBackend::ObjectHandler
     */
    class DevWindow : public QMainWindow, public TranslatableWindow {
    Q_OBJECT

    public:
        /**
         * @brief Constructor for the DevWindow class.
         * @ingroup Constructructors-Destructors
         *
         * @details
         * This constructor initializes the DevWindow object with a parent widget and an ObjectHandler object.
         *
         * @param parent Pointer to the parent widget.
         * @param objectHandler Shared pointer to the ObjectHandler object.
         */
        explicit DevWindow(QWidget *parent,
                           QSharedPointer<AposBackend::ObjectHandler> objectHandler,
                           QSharedPointer<AposLogger::Logger> newLogger);

        /**
         * @brief Destructor for the DevWindow class.
         * @ingroup Constructructors-Destructors
         *
         * @details
         * This destructor cleans up the DevWindow object.
         */
        ~DevWindow() override;

        /**
         * @brief Logs an event with a type and a message.
         *
         * @details
         * This function logs an event with a specified type and message.
         *
         * @param type The type of the event.
         * @param message The message of the event.
         */
        void logEvent(const QString &type, const QString &message);

        /**
         * @brief Logs an event with a message and a SQL error.
         * @ingroup Log-Functions
         *
         * @details
         * This function logs an event with a specified message and a SQL error.
         *
         * @param message The message of the event.
         * @param error The SQL error of the event.
         */
        void logEvent(const QString &message, const QSqlError &error);

        /**
         * @brief Logs an event with a message.
         * @ingroup Log-Functions
         *
         * @details
         * This function logs an event with a specified message.
         *
         * @param message The message of the event.
         */
        void logEvent(const QString &message);

        /**
         * @brief Retranslates the user interface.
         * @ingroup Ui-Functions
         *
         * @details
         * This function retranslates the user interface of the DevWindow object.
         */
        void retranslateUi() override;

    signals:

        /**
         * @brief Signal for returning to the launcher.
         * @ingroup Signal-Funtions
         * @details
         * This signal is emitted when the user wants to return to the launcher.
         */
        void returnToLauncher();

        /**
         * @brief Signal for opening the settings.
         * @ingroup Signal-Funtions
         *
         * @details
         * This signal is emitted when the user wants to open the settings.
         */
        void openSettings();

    private slots:

        /**
         * @brief Slot for the 'InitDB' button click event.
         * @ingroup Slot-Functions
         *
         * @details
         * This slot is triggered when the 'InitDB' button is clicked.
         */
        void initDbClicked();

        /**
         * @brief Slot for the 'CloseDB' button click event.
         * @ingroup Slot-Functions
         *
         * @details
         * This slot is triggered when the 'CloseDB' button is clicked.
         */
        void closeDbClicked();

        /**
         * @brief Slot for the 'Execute' button click event.
         * @ingroup Slot-Functions
         *
         * @details
         * This slot is triggered when the 'Execute' button is clicked.
         */
        void executeClicked();

        /**
         * @brief Slot for the 'SelectTable' button click event.
         * @ingroup Slot-Functions
         *
         * @details
         * This slot is triggered when the 'SelectTable' button is clicked.
         */
        void selectTableClicked();

        /**
         * @brief Slot for the 'Add' button click event.
         * @ingroup Slot-Functions
         *
         * @details
         * This slot is triggered when the 'Add' button is clicked.
         */
        void addValuesClicked();

        /**
         * @brief Slot for the 'Update' button click event.
         * @ingroup Slot-Functions
         *
         * @details
         * This slot is triggered when the 'Update' button is clicked.
         */
        void updateTableClicked();

        /**
         * @brief Slot for the 'clearCommandAfterExecute' state change event.
         * @ingroup Slot-Functions
         *
         * @details
         * This slot is triggered when the state of the 'clearCommandAfterExecute' checkbox is changed.
         *
         * @param arg1 The new state of the checkbox.
         */
        void clearCommandAfterExecuteStateChanged(int arg1);

        /**
         * @brief Slot for the 'clearInputsAfterInsert' state change event.
         * @ingroup Slot-Functions
         *
         * @details
         * This slot is triggered when the state of the 'clearInputsAfterInsert' checkbox is changed.
         *
         * @param arg1 The new state of the checkbox.
         */
        void clearInputsAfterInsertStateChanged(int arg1);

        /**
         * @brief Slot for the 'ReturnToLauncher' button click event.
         * @ingroup Slot-Functions
         *
         * @details
         * This slot is triggered when the 'ReturnToLauncher' button is clicked.
         */
        void returnToLauncherClicked();

        /**
         * @brief Slot for the 'Settings' button click event.
         * @ingroup Slot-Functions
         *
         * @details
         * This slot is triggered when the 'Settings' button is clicked.
         */
        void settingsClicked();

    private:

        /**
         * @brief Connects the user interface signals and slots.
         * @ingroup Ui-Functions
         *
         * @details This function is responsible for connecting the user interface signals to their corresponding slots.
         * It should be called after the user interface has been set up, typically in the constructor of the class.
         */
        void devConnectUi();

        /**
         * @brief Initializes the database.
         * @ingroup Database-Functions
         *
         * @details
         * This function initializes the database of the DevWindow object.
         */
        void initDatabase();

        /**
         * @brief Closes the database.
         * @ingroup Database-Functions
         *
         * @details
         * This function closes the database of the DevWindow object.
         *
         * @param db Shared pointer to the DatabaseHandler object.
         */
        void closeDatabase(const QSharedPointer<AposDatabase::DatabaseHandler> &db);

        /**
         * @brief Sets the model views.
         * @ingroup Database-Functions
         *
         * @details
         * This function sets the model views of the DevWindow object.
         */
        void setModelViews();

        /**
         * @brief Sets the model views with a table model.
         * @ingroup Database-Functions
         *
         * @details
         * This function sets the model views of the DevWindow object with a specified table model.
         *
         * @param tableModel Shared pointer to the QSqlTableModel object.
         */
        void setModelViews(const QSharedPointer<QSqlTableModel> &tableModel);

        /**
         * @brief Enables or disables the buttons.
         * @ingroup Ui-Functions
         *
         * @details
         * This function enables or disables the buttons of the DevWindow object based on whether the database is loaded.
         *
         * @param databaseLoaded Boolean value indicating whether the database is loaded.
         */
        void enableButtons(bool databaseLoaded);

        /**
         * @brief Assigns the inputs.
         * @ingroup Ui-Functions
         *
         * @details
         * This function assigns the inputs of the DevWindow object.
         */
        void assignInputs();

        /**
         * @brief Clears the inputs.
         * @ingroup Ui-Functions
         *
         * @details
         * This function clears the inputs of the DevWindow object based on a specified boolean value.
         *
         * @param clearBool Boolean value indicating whether to clear the inputs.
         */
        void clearInputs(bool clearBool);

        /**
         * @brief Checks a checkbox.
         * @ingroup Ui-Functions
         *
         * @details
         * This function checks a checkbox of the DevWindow object based on a specified integer value.
         *
         * @param argCb Integer value indicating the state of the checkbox.
         * @return Boolean value indicating whether the checkbox is checked.
         */
        bool checkCheckbox(int argCb);

        /**
         * @brief Clears the command box.
         * @ingroup Ui-Functions
         *
         * @details
         * This function clears the command box of the DevWindow object based on a specified boolean value.
         *
         * @param clearBool Boolean value indicating whether to clear the command box.
         */
        void clearCommandBox(bool clearBool);

        /**
         * @brief Pointer to the user interface of the DevWindow object.
         * @ingroup Variables
         *
         * @details
         * This pointer is used to access the user interface of the DevWindow object.
         */
        Ui::DevWindow *ui;

        /**
         * @brief Shared pointer to the ObjectHandler object.
         * @ingroup Variables
         *
         * @details
         * This shared pointer is used to access the ObjectHandler object.
         */
        QSharedPointer<AposBackend::ObjectHandler> ptrObjectHandler = nullptr;

        /**
         * @brief Shared pointer to the Logger object.
         * @ingroup Variables
         *
         * @details
         * This shared pointer is used to access the Logger object.
         */
        QSharedPointer<AposLogger::Logger> ptrLogger = nullptr;

        /**
         * @brief String values for the inputs.
         * @ingroup Variables
         *
         * @details
         * These string values are used to store the inputs of the DevWindow object.
         */
        QString input1, input2, input3, input4, input5;

        /**
         * @brief Boolean values for clearing the command and the inputs.
         * @ingroup Variables
         *
         * @details
         * These boolean values are used to determine whether to clear the command, and the inputs of the DevWindow object.
         */
        bool clearCommand = false, clearInput = false;
    };

}