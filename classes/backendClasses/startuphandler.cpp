/**
 * @file StartupHandler.cpp
 * @brief Implementation file for the StartupHandler class.
 * @date 13.11.2023
 * @version 1.1.1
 * @author Simon Blum
 */

#include "startuphandler.hpp"

StartupHandler::StartupHandler(QApplication *application)
{
    this->ptrApplication = application;
}

StartupHandler::~StartupHandler()
{
    qDebug() << "StartupHandler deleted!";
}

ObjectHandler* StartupHandler::startUp()
{

    initObjectHandler();
    initTranslator();
    return objectHandler;

}

void StartupHandler::initTranslator()
{
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Apos-DatabaseManager_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            ptrApplication->installTranslator(&translator);
            break;
        }
    }
}

void StartupHandler::initObjectHandler()
{
    DatabaseHandler *dbHandler = new DatabaseHandler();
    TableHandler *tableHandler = new TableHandler();
    objectHandler = new ObjectHandler(ptrApplication, dbHandler, tableHandler);
}

