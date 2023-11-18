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
    StartupHandler::StartupHandler(const QSharedPointer<QApplication> &application) {
        if (application == nullptr) {
            throw std::runtime_error("QApplication pointer is null");
        }
        this->ptrApplication = application;
    }
    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<ObjectHandler> StartupHandler::startUp() {
        try {
            installTranslator();
            ptrObjectHandler = initObjectHandler();
        } catch (const std::exception &e) {
            qDebug() << "Exception caught in StartupHandler::startUp: " << e.what();
            ptrObjectHandler = nullptr;
        }
        return ptrObjectHandler;
    }
    //----------------------------------------------------------------------------------------------------------------//
    void StartupHandler::installTranslator() {
        QSharedPointer<QTranslator> translator = initTranslator();
        if (ptrApplication->installTranslator(translator.data())) {
            qDebug() << "Translator installed";
        }
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
            throw std::runtime_error("Failed to load translator");
        }
        return translator;
    }
    //----------------------------------------------------------------------------------------------------------------//
    QSharedPointer<ObjectHandler> StartupHandler::initObjectHandler() {
        QSharedPointer<AposDatabase::DatabaseHandler> dbHandler(new AposDatabase::DatabaseHandler());
        QSharedPointer<AposDatabase::TableHandler> tableHandler(new AposDatabase::TableHandler(dbHandler));
        if (dbHandler == nullptr || tableHandler == nullptr) {
            throw std::runtime_error("Failed to initialize DatabaseHandler or TableHandler");
        }
        return QSharedPointer<ObjectHandler>(new ObjectHandler(ptrApplication, dbHandler, tableHandler));
    }

}