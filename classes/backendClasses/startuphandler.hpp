/**
 * @file StartupHandler.hpp
 * @brief Header file for the StartupHandler class.
 * @date 13.11.2023
 * @version 1.1.1
 * @author Simon Blum
 */

#pragma once

#include <QDebug>
#include <QtSql>
#include <QLocale>
#include <QTranslator>

#include "basicClasses/objecthandler.hpp"

/**
 * @defgroup StartupHandlerGroup StartupHandler
 * @{
 */

/**
 * @brief The StartupHandler class manages the startup procedures of the application.
 * @details This class initializes necessary components during application startup, such as translators and object handlers.
 */
class StartupHandler
{
public:

    /**
     * @addtogroup ConstructorsDestructorsGroup
     * @{
     */

    /**
     * @brief Constructs a StartupHandler object.
     * @details Initializes an instance of StartupHandler.
     *
     * @param a The QApplication instance.
     */
    StartupHandler(QApplication* application);

    ~StartupHandler();

    ///@}

    /**
     * @brief Starts up the application.
     * @details Initializes translators, creates necessary object handlers, and performs startup procedures.
     */
    ObjectHandler* startUp();


private:

    /**
     * @addtogroup InitializationGroup
     * @{
     */

    /**
     * @brief Initializes the translator for internationalization.
     * @details Loads the translator based on the system's UI languages and installs it to the QApplication.
     */
    void initTranslator();

    void initObjectHandler();

    /// @}

    QApplication *ptrApplication; /**< The QApplication instance. */

    ObjectHandler *objectHandler; /**< The ObjectHandler instance. */
};

/**
 * @} // end of StartupHandlerGroup
 */
