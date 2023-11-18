/**
 * @file startuphandler.hpp
 * @brief Defines the StartupHandler class.
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.1
 * @license LGPL-V3
 *
 * This file contains the definition of the StartupHandler class, which is
 * responsible for initializing the application's translator and ObjectHandler.
 *
 * The StartupHandler class encapsulates the startup logic of the application
 * and provides a simple interface for starting up the application.
 *
 * @details The StartupHandler class is part of the application's backend logic.
 * It interacts with the QApplication object and uses the ObjectHandler class
 * to manage the application's objects.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 * Therefore, the LGPL-V3 licence is used instead of the commercial Qt licence.
 *
 * @see ObjectHandler
 */
#pragma once

#include <QDebug>
#include <QtSql>
#include <QLocale>
#include <QTranslator>

#include "objecthandler.hpp"

namespace AposBackend {

/**
 * @class StartupHandler
 * @brief Handles the startup process of the application.
 *
 * The StartupHandler class is responsible for initializing the application's
 * translator and ObjectHandler. It encapsulates the startup logic of the
 * application and provides a simple interface for starting up the application.
 */
    class StartupHandler {
    public:
        /**
         * @brief Constructs a StartupHandler object.
         *
         * This constructor initializes the StartupHandler object with a pointer
         * to the QApplication object.
         *
         * @param application Pointer to the QApplication object.
         * @throws std::runtime_error if the QApplication pointer is null.
         */
        explicit StartupHandler(const QSharedPointer<QApplication> &application);

        /**
         * @brief Starts up the application.
         *
         * This method initializes the application's translator and ObjectHandler,
         * and returns a pointer to the initialized ObjectHandler.
         *
         * @return Pointer to the initialized ObjectHandler.
         * @throws std::runtime_error if the translator or ObjectHandler fails to initialize.
         */
        QSharedPointer<ObjectHandler> startUp();

    private:
        /**
         * @brief Initializes the application's translator.
         *
         * This method creates and initializes a QTranslator object with the system's
         * locale, and returns the initialized QTranslator.
         *
         * @return Pointer to the initialized QTranslator.
         * @throws std::runtime_error if the translator fails to load.
         */
        QSharedPointer<QTranslator> initTranslator();

        /**
         * @brief Installs the application's translator.
         *
         * This method initializes a QTranslator object by calling the initTranslator method,
         * and installs the translator into the QApplication object. The translator enables
         * the application to show UI text in different languages.
         *
         * @throws std::runtime_error if the translator fails to load.
         */
        void installTranslator();

        /**
         * @brief Initializes the application's ObjectHandler.
         *
         * This method creates and initializes an ObjectHandler object, and returns
         * the initialized ObjectHandler.
         *
         * @return Pointer to the initialized ObjectHandler.
         * @throws std::runtime_error if the ObjectHandler fails to initialize.
         */
        QSharedPointer<ObjectHandler> initObjectHandler();

        QSharedPointer<QApplication> ptrApplication; /**< Pointer to the QApplication object. */
        QSharedPointer<ObjectHandler> ptrObjectHandler; /**< Scoped pointer to the ObjectHandler object. */
    };

} // namespace AposBackend