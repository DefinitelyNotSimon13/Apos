/**
 * @file startuphandler.hpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Header file for the StartupHandler class.
 *
 * @details This file contains the declaration of the StartupHandler class, which is a part of the application's backend logic.
 * The StartupHandler class provides the functionality for initializing the application's translator and ObjectHandler.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see ObjectHandler
 * @see QApplication
 * @see QSharedPointer
 * @see QDebug
 * @see QtSql
 * @see QTranslator
 * @see QLocale
 */
#pragma once

#include <QDebug>
#include <QtSql>
#include <QLocale>
#include <QTranslator>

#include "objecthandler.hpp"
#include "Logger.hpp"

//--------------------------------------------------------------------------------------------------------------------//
namespace AposBackend {
    /**
     * @class StartupHandler
     * @ingroup Initialization
     * @brief Provides the functionality for initializing the application's translator and ObjectHandler.
     * @details The StartupHandler class is a part of the application's backend logic.
     * It interacts with the QApplication object and uses the ObjectHandler class
     * to manage the application's objects.
     *
     * @see ObjectHandler
     * @see QApplication
     * @see QSharedPointer
     * @see QDebug
     * @see QtSql
     * @see QTranslator
     * @see QLocale
     */
    class StartupHandler {
    public:
        /**
         * @brief Constructor for the StartupHandler class.
         * @ingroup Constructructors-Destructors
         * @details This constructor initializes the StartupHandler object with a QApplication object and a Logger object.
         * @param application Shared pointer to the QApplication object.
         * @param logger Shared pointer to the Logger object.
         */
        explicit StartupHandler(const QSharedPointer<QApplication> &application,
                                const QSharedPointer<AposLogger::Logger> &logger);

        /**
         * @brief Initializes the application's translator and ObjectHandler.
         * @ingroup Initialization
         * @details This function initializes the application's translator and ObjectHandler.
         * @return Shared pointer to the initialized ObjectHandler object.
         */
        QSharedPointer<ObjectHandler> startUp();

    private:
        /**
         * @brief Initializes the application's translator.
         * @ingroup Initialization
         * @details This function initializes the application's translator.
         * @return Shared pointer to the initialized QTranslator object.
         */
        QSharedPointer<QTranslator> initTranslator();

        /**
         * @brief Installs the application's translator.
         * @ingroup Initialization
         * @details This function installs the application's translator.
         */
        void installTranslator();

        /**
         * @brief Initializes the application's ObjectHandler.
         * @ingroup Initialization
         * @details This function initializes the application's ObjectHandler.
         * @return Shared pointer to the initialized ObjectHandler object.
         */
        QSharedPointer<ObjectHandler> initObjectHandler();

        /**
         * @brief Shared pointer to the QApplication object.
         * @ingroup Variables
         * @details This shared pointer is used to access the QApplication object.
         */
        QSharedPointer<QApplication> ptrApplication;

        /**
         * @brief Shared pointer to the Logger object.
         * @ingroup Variables
         * @details This shared pointer is used to access the Logger object.
         */
        QSharedPointer<AposLogger::Logger> ptrLogger;

    };
}