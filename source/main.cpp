/**
 * @file main.cpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Main entry point for the application.
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
namespace AppInitialization {
    /**
     * @brief Initialize the StartupHandler object
     *
     * This function initializes the StartupHandler object with the QApplication object.
     *
     * @param newApp Shared pointer to the QApplication object. This is used to initialize the StartupHandler object.
     * @return Shared pointer to the initialized StartupHandler object
     * @throws std::runtime_error if the QApplication pointer is null.
     */
    QSharedPointer<AposBackend::StartupHandler> initializeStartupHandler(const QSharedPointer<QApplication>& newApp);

    /**
     * @brief Initialize the ObjectHandler object
     *
     * This function initializes the StartupHandler object with the QApplication object,
     * then uses the StartupHandler object to initialize and return the ObjectHandler object.
     *
     * @param startupHandler Pointer to the StartupHandler object. This is used to initialize the ObjectHandler object.
     * @return Unique pointer to the initialized ObjectHandler object
     * @throws std::runtime_error if the QApplication pointer is null or if the ObjectHandler fails to initialize.
     */
    QSharedPointer<AposBackend::ObjectHandler> initializeObjectHandler(
            const QSharedPointer<AposBackend::StartupHandler>& startupHandler);
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
    QSharedPointer<AposFrontend::WindowHandler>
    initializeWindowHandler(const QSharedPointer<AposBackend::ObjectHandler>& objectHandler);
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

        QSharedPointer<AposBackend::StartupHandler>
                startupHandler = AppInitialization::initializeStartupHandler(application);
        QSharedPointer<AposBackend::ObjectHandler>
                objectHandler = AppInitialization::initializeObjectHandler(startupHandler);
        QSharedPointer<AposFrontend::WindowHandler> windowHandler = AppInitialization::initializeWindowHandler(
                objectHandler);

        returnStatus = QApplication::exec(); // Update return status
    } catch (const std::exception &e) {
        qDebug() << "Exception caught in main: " << e.what();
    }
    return returnStatus; // Single point of exit
}
// ------------------------------------------------------------------------------------------------------------------ //
namespace AppInitialization {
    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<AposBackend::StartupHandler> initializeStartupHandler(const QSharedPointer<QApplication>& newApp) {
        if (newApp == nullptr) {
            throw std::runtime_error("QApplication pointer is null");
        }

        QSharedPointer<AposBackend::StartupHandler> startupHandler(new AposBackend::StartupHandler(newApp));
        qDebug() << "StartupHandler Object initialized";
        return startupHandler;
    }
    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<AposBackend::ObjectHandler>
    initializeObjectHandler(const QSharedPointer<AposBackend::StartupHandler>& startupHandler) {

        QSharedPointer<AposBackend::ObjectHandler> objectHandler(startupHandler->startUp());
        if (objectHandler == nullptr) {
            throw std::runtime_error("Failed to initialize ObjectHandler");
        }
        qDebug() << "ObjectHandler Object initialized";

        return objectHandler;
    }
    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<AposFrontend::WindowHandler>
    initializeWindowHandler(const QSharedPointer<AposBackend::ObjectHandler>& objectHandler) {
        if (objectHandler == nullptr) {
            throw std::runtime_error("ObjectHandler pointer is null");
        }

        QSharedPointer<AposFrontend::WindowHandler> windowHandler(new AposFrontend::WindowHandler(objectHandler));
        windowHandler->showLaunchWindow();
        qDebug() << "After DevWindow Show";

        return windowHandler;
    }
}
// End of file main.cpp --------------------------------------------------------------------------------------------- //
// Doxygen-Groups --------------------------------------------------------------------------------------------------- //

/**
 * @defgroup Constructructors-Destructors Constructors and Desctructors
 * @brief Group of constructors and destructors in the application.
 *
 * @details
 * This group contains all the constructors and destructors used in the application.
 * These functions are responsible for initializing and cleaning up objects.
 */

/**
 * @defgroup Initialization Initialization
 * @brief Group of initialization functions in the application.
 *
 * @details
 * This group contains all the functions that are responsible for initializing various components of the application,
 * such as the QApplication, StartupHandler, ObjectHandler, and WindowHandler objects.
 */

/**
 * @defgroup Slot-Functions Slot Functions
 * @brief Group of slot functions in the application.
 *
 * @details
 * This group contains all the slot functions in the application.
 * These functions are used to handle signals emitted by other objects.
 */

/**
* @defgroup Signal-Funtions Signal Functions
* @brief Group of signal functions in the application.
*
* @details
* This group contains all the signal functions in the application.
* These functions are used to emit signals that can be handled by slot functions.
*/

/**
 * @defgroup Ui-Functions UI Functions
 * @brief Group of UI functions in the application.
 *
 * @details
 * This group contains all the functions that are responsible for handling the user interface of the application.
 */

/**
 * @defgroup Database-Functions Database Functions
 * @brief Group of database functions in the application.
 *
 * @details
 * This group contains all the functions that interact with the database.
 * These functions are responsible for creating, reading, updating, and deleting data in the database.
 */

/**
 * @defgroup Log-Functions Log Functions
 * @brief Group of log functions in the application.
 *
 * @details
 * This group contains all the functions that are responsible for logging information.
 * These functions are used to log information for debugging and tracking purposes.
 */

/**
 * @defgroup Utility-Functions Utility Functions
 * @brief Group of utility functions in the application.
 *
 * @details
 * This group contains all the utility functions in the application.
 * These functions provide various utility services such as string manipulation, data conversion, etc.
 */

/**
 * @defgroup Variables Variables
 * @brief Group of variables in the application.
 *
 * @details
 * This group contains all the variables used in the application.
 * These variables are used to store data and pass it between functions.
 */
