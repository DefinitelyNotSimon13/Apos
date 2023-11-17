/**
 * @file main.cpp
 * @brief Main file for the program
 * @details Main file for the program
 * @date 13.11.2023
 * @author Simon Blum
 * @version 1.1.1
 */
#include "interfaceClasses/devwindow.hpp"
#include "interfaceClasses/launcherwindow.hpp"
#include "basicClasses/startuphandler.hpp"
#include "interfaceClasses/windowhandler.hpp"

#include <QApplication>
#include <QDebug>
#include <QtSql>

/**
 * @brief The main funtion for the program
 * @details The main function for the program, which sets up the QApplication using the startupHandler class, then sets up
 *          the window and runs the application loop.
 * @param argc The number of arguments
 * @param argv The arguments
 * @return The exit code
 */
int main(int argc, char *argv[])
{
    //! The QApplication object
    QApplication *a = new QApplication(argc, argv);
    qDebug() << "Application Object initialized";

    //! The StartupHandler object
    StartupHandler startupHandler(a);
    qDebug() << "StartupHandler Object initialized";

    //! Start up the program
    ObjectHandler *objectHandler = startupHandler.startUp();
    qDebug() << "ObjectHandler Object initialized";
    startupHandler.~StartupHandler();

    WindowHandler windowHandler(objectHandler);
    windowHandler.showLaunchWindow();

    /*//! The DevWindow object
    DevWindow devWindow(nullptr, objectHandler);
    //! Show the DevWindow
    devWindow.show();*/

    qDebug() << "After DevWindow Show";


    //! Return the exit code
    return a->exec();
}
