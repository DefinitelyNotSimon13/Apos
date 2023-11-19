/**
 * @file startuphandler.cpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Source file for the StartupHandler class.
 *
 * @details This file contains the implementation of the StartupHandler class, which is a part of the application's backend logic.
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
#include "startuphandler.hpp"

namespace AposBackend {
    //----------------------------------------------------------------------------------------------------------------//
    StartupHandler::StartupHandler(const QSharedPointer<QApplication> &application,
                                   const QSharedPointer<AposLogger::Logger> &logger) {
        if (application == nullptr || logger == nullptr) {
            throw QException();
        }
        this->ptrApplication = application;
        this->ptrLogger = logger;
        ptrLogger->log("init", "StartupHandler initialized");
    }

    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<ObjectHandler> StartupHandler::startUp() {
        QSharedPointer<ObjectHandler> ptrObjectHandler = nullptr;
        try {
            installTranslator();
            ptrObjectHandler = initObjectHandler();
        } catch (const QException &e) {
            ptrLogger->log("caught exception", e.what());
            ptrObjectHandler = nullptr;
        }
        ptrLogger->log("init", "StartupHandler finished, returning ObjectHandler");
        return ptrObjectHandler;
    }

    //----------------------------------------------------------------------------------------------------------------//
    void StartupHandler::installTranslator() {
        QSharedPointer<QTranslator> translator = initTranslator();
        if (!ptrApplication->installTranslator(translator.data())) {
            ptrLogger->error("Failed to install translator", "installTranslator()", "StartupHandler", "");
        }
        ptrLogger->log("init", "Translator installed");
    }

    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<QTranslator> StartupHandler::initTranslator() {
        QSharedPointer<QTranslator> translator(new QTranslator());
        const QStringList uiLanguages = QLocale::system().uiLanguages();
        for (const QString &locale: uiLanguages) {
            const QString baseName = "Apos-DatabaseManager_" + QLocale(locale).name();
            if (translator->load(":/i18n/" + baseName)) {
                break;
            }
        }
        if (translator->isEmpty()) {
            ptrLogger->error("Failed to load translator", "initTranslator()", "StartupHandler", "");
        }
        ptrLogger->log("init", "Translator loaded");
        return translator;
    }

    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<ObjectHandler> StartupHandler::initObjectHandler() {
        QSharedPointer<AposDatabase::DatabaseHandler> dbHandler(new AposDatabase::DatabaseHandler(ptrLogger));
        QSharedPointer<AposDatabase::TableHandler> tableHandler(new AposDatabase::TableHandler(dbHandler, ptrLogger));
        if (dbHandler == nullptr || tableHandler == nullptr) {
            ptrLogger->error("Failed to initialize ObjectHandler", "initObjectHandler()", "StartupHandler", "");
        }
        return QSharedPointer<ObjectHandler>(new ObjectHandler(ptrApplication, dbHandler, tableHandler, ptrLogger));
    }
}