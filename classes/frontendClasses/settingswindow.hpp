/**
 * @file settingswindow.hpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Header file for the SettingsWindow class.
 *
 * @details This file contains the declaration of the SettingsWindow class, which is a part of the application's frontend logic.
 * The SettingsWindow class inherits from QWidget and TranslatableWindow, and it provides the user interface for the settings window.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see AposBackend::ObjectHandler
 * @see TranslatableWindow
 * @see QWidget
 * @see QTranslator
 * @see QSharedPointer
 */

#pragma once

#include <QWidget>
#include <QDebug>
#include <QTranslator>
#include "../backendClasses/objecthandler.hpp"
#include "translatablewindow.hpp"
#include "../backendClasses/logger.hpp"


//--------------------------------------------------------------------------------------------------------------------//
namespace Ui {
    class SettingsWindow;
}
//--------------------------------------------------------------------------------------------------------------------//
namespace AposFrontend {
    /**
     * @class SettingsWindow
     * @ingroup Ui-Functions
     * @brief Provides the user interface for the settings window.
     * @details The SettingsWindow class provides the functionality for applying settings and retranslating the user interface.
     * It interacts with the QWidget and TranslatableWindow classes and uses the ObjectHandler class
     * to manage the application's objects.
     *
     * @see AposBackend::ObjectHandler
     * @see TranslatableWindow
     * @see QWidget
     * @see QTranslator
     * @see QSharedPointer
     */
    class SettingsWindow : public QWidget, public TranslatableWindow {
    Q_OBJECT

    public:
        /**
         * @brief Constructor for the SettingsWindow class.
         * @ingroup Constructructors-Destructors
         * @details This constructor initializes the SettingsWindow object with a parent widget and an ObjectHandler object.
         * @param parent Pointer to the parent widget.
         * @param newObjectHandler Shared pointer to the ObjectHandler object.
         */
        explicit SettingsWindow(QWidget *parent,
                                QSharedPointer<AposBackend::ObjectHandler> newObjectHandler,
                                QSharedPointer<AposLogger::Logger> newLogger);

        /**
         * @brief Destructor for the SettingsWindow class.
         * @ingroup Constructructors-Destructors
         * @details This destructor cleans up the SettingsWindow object.
         */
        ~SettingsWindow() override;

        /**
         * @brief Retranslates the user interface.
         * @ingroup Ui-Functions
         * @details This function retranslates the user interface of the SettingsWindow object.
         */
        void retranslateUi() override;

    signals:

        /**
         * @brief Signal for applying settings.
         * @ingroup Signal-Funtions
         * @details This signal is emitted when the user applies the settings.
         */
        void appliedSettings();

    private slots:

        /**
         * @brief Slot for the 'Close' button click event.
         * @ingroup Slot-Functions
         * @details This slot is triggered when the 'Close' button is clicked.
         */
        void closeClicked();

        /**
         * @brief Slot for the 'Apply' button click event.
         * @ingroup Slot-Functions
         * @details This slot is triggered when the 'Apply' button is clicked.
         */
        void applyClicked();

        /**
         * @brief Slot for the 'Apply and Close' button click event.
         * @ingroup Slot-Functions
         * @details This slot is triggered when the 'Apply and Close' button is clicked.
         */
        void applyAndCloseClicked();

        /**
         * @brief Slot for the 'Language' combo box index change event.
         * @ingroup Slot-Functions
         * @details This slot is triggered when the index of the 'Language' combo box is changed.
         * @param index The new index of the combo box.
         */
        void languageCurrentIndexChanged(int index);

    private:
        /**
         * @brief Connects the user interface.
         * @ingroup Ui-Functions
         * @details This function connects the user interface of the SettingsWindow object.
         */
        void settingsConnectUi();

        /**
         * @brief Installs the application's translator.
         * @ingroup Initialization
         * @details This function installs the application's translator.
         */
        void installTranslator();

        /**
         * @brief Pointer to the user interface of the SettingsWindow object.
         * @ingroup Variables
         * @details This pointer is used to access the user interface of the SettingsWindow object.
         */
        Ui::SettingsWindow *ui;

        /**
         * @brief Shared pointer to the ObjectHandler object.
         * @ingroup Variables
         * @details This shared pointer is used to access the ObjectHandler object.
         */
        QSharedPointer<AposBackend::ObjectHandler> ptrObjectHandler = nullptr;

        /**
         * @brief Shared pointer to the QTranslator object.
         * @ingroup Variables
         * @details This shared pointer is used to access the QTranslator object.
         */
        QSharedPointer<QTranslator> ptrTranslator = nullptr;

        /**
         * @brief Shared pointer to the Logger object.
         * @ingroup Variables
         * @details This shared pointer is used to access the Logger object.
         */
        QSharedPointer<AposLogger::Logger> ptrLogger = nullptr;

        /**
         * @brief The index of the selected language.
         * @ingroup Variables
         * @details This variable is used to store the index of the selected language.
         */
        int languageIndex{};

        /**
         * @brief The temporary index of the selected language.
         * @ingroup Variables
         * @details This variable is used to store the temporary index of the selected language.
         */
        int tempLanguageIndex{};

        /**
         * @brief Indicates whether the language has changed.
         * @ingroup Variables
         * @details This variable is used to indicate whether the language has changed.
         */
        bool languageChanged{};
    };
}