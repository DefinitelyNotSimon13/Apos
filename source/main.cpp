/**
 * @file main.cpp
 * @brief Main entry point for the application.
 * @author Simon Blum
 * @date 13.11.2023
 * @version 1.0.0
 * @license LGPL-V3
 *
 * This file contains the main function, which represents the entry point for the application.
 * It initializes the QApplication, StartupHandler, and ObjectHandler objects.
 * It also creates a WindowHandler object and shows the launch window.
 *
 * @details The application is built using the Qt framework and follows the object-oriented programming paradigm.
 * The main function initializes the necessary objects and starts the application's event loop.
 * The QApplication object encapsulates the functionality of Qts core application class for GUI-based applications.
 * The StartupHandler, ObjectHandler, and WindowHandler classes are part of the
 * application's backend and frontend logic.
 *
 * @deviation MISRA 3-1-3
 * The argv parameter in the main function is a pointer to an array of C-style strings.
 * This array is not explicitly sized, which violates MISRA rule 3-1-3.
 * However, the parameters of the main function are defined by the C++ standard,
 * and changing them would not be compliant with the standard.
 * This deviation is considered acceptable because the size of the argv array is
 * managed by the runtime environment, and the array is guaranteed to be null-terminated.
 * Therefore, the risk of out-of-bounds access is minimal.
 *
 * @deviation MISRA 7-3-1
 * The main – defined as qMain – function is part of the global namespace, which violates MISRA rule 7-3-1. However,
 * since the qMain function acts as the main function within the Qt framework, this deviation is considered acceptable.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 * Therefore, the LGPL-V3 licence is used instead of the commercial Qt licence.
 *
 * @see QApplication
 * @see StartupHandler
 * @see ObjectHandler
 * @see WindowHandler
 */

// Local includes --------------------------------------------------------------------------------------------------- //
#include "../classes/backendClasses/startuphandler.hpp" /**< Include the StartupHandler class */
#include "../classes/frontendClasses/windowhandler.hpp" /**< Include the WindowHandler class */

// System includes -------------------------------------------------------------------------------------------------- //
#include <QApplication> /**< Include the QApplication class */
#include <QDebug> /**< Include the QDebug class for debugging */
#include <QScopedPointer> /**< Include the QScopedPointer class for memory management */

// Declaration of functions------------------------------------------------------------------------------------------ //
namespace appInitialization {
    /**
     * @brief Initialize the ObjectHandler object
     *
     * This function initializes the StartupHandler object with the QApplication object,
     * then uses the StartupHandler object to initialize and return the ObjectHandler object.
     *
     * @param app Pointer to the QApplication object. This is used to initialize the StartupHandler object.
     * @return Unique pointer to the initialized ObjectHandler object
     * @throws std::runtime_error if the QApplication pointer is null or if the ObjectHandler fails to initialize.
     */
    QSharedPointer<ObjectHandler> initializeObjectHandler(QSharedPointer<QApplication> &app);

// ------------------------------------------------------------------------------------------------------------------ //

    /**
     * @brief Initialize the WindowHandler object
     *
     * This function initializes the WindowHandler object with the ObjectHandler object and shows the launch window.
     *
     * @param objectHandler Unique pointer to the ObjectHandler object. This is used to
     *                      initialize the WindowHandler object.
     * @return Unique pointer to the initialized WindowHandler object
     * @throws std::runtime_error if the ObjectHandler pointer is null, or if
     *                            the WindowHandler object fails to initialize.
     */
    QSharedPointer<WindowHandler> initializeWindowHandler(const QSharedPointer<ObjectHandler> &objectHandler);
}

// Implementation of functions -------------------------------------------------------------------------------------- //
/**
 * @brief Main function
 *
 * This is the main function, which is the entry point for the application.
 * It initializes the QApplication, ObjectHandler, and WindowHandler objects,
 * and starts the application's event loop.
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @return int Application exit status
 */
int main(int argc, char *argv[]) { // NOLINT(clion-misra-cpp2008-3-1-3, clion-misra-cpp2008-7-3-1)
    int returnStatus = -1; // Initialize return status to -1 (error state)
    try {
        QSharedPointer<QApplication> application(new QApplication(argc, argv));
        qDebug() << "Application Object initialized";

        QSharedPointer<ObjectHandler> objectHandler = appInitialization::initializeObjectHandler(application);
        QSharedPointer<WindowHandler> windowHandler = appInitialization::initializeWindowHandler(objectHandler);

        returnStatus = QApplication::exec(); // Update return status
    } catch (const std::exception &e) {
        qDebug() << "Exception caught in main: " << e.what();
    }
    return returnStatus; // Single point of exit
}

// ------------------------------------------------------------------------------------------------------------------ //
namespace appInitialization {
    QSharedPointer<ObjectHandler> initializeObjectHandler(QSharedPointer<QApplication> &app) {
        if (app == nullptr) {
            throw std::runtime_error("QApplication pointer is null");
        }

        StartupHandler startupHandler(app.data());
        qDebug() << "StartupHandler Object initialized";

        QSharedPointer<ObjectHandler> objectHandler(startupHandler.startUp());
        if (objectHandler == nullptr) {
            throw std::runtime_error("Failed to initialize ObjectHandler");
        }
        qDebug() << "ObjectHandler Object initialized";

        return objectHandler;
    }

    QSharedPointer<WindowHandler> initializeWindowHandler(const QSharedPointer<ObjectHandler> &objectHandler) {
        if (objectHandler == nullptr) {
            throw std::runtime_error("ObjectHandler pointer is null");
        }

        QSharedPointer<WindowHandler> windowHandler(new WindowHandler(objectHandler.data()));
        windowHandler->showLaunchWindow();
        qDebug() << "After DevWindow Show";

        return windowHandler;
    }
}
// -----------------------------------------------------------------------------