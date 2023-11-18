/**
 * @file startuphandler.cpp
 * @brief Implements the StartupHandler class.
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.1
 * @license LGPL-V3
 *
 * This file contains the implementation of the StartupHandler class, which is
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
#include "startuphandler.hpp"

namespace AposBackend {

    StartupHandler::StartupHandler(const QSharedPointer<QApplication> &application) {
        if (application == nullptr) {
            throw std::runtime_error("QApplication pointer is null");
        }
        this->ptrApplication = application;
    }

    QSharedPointer <ObjectHandler> StartupHandler::startUp() {
        try {
            installTranslator();
            ptrObjectHandler = initObjectHandler();
        } catch (const std::exception &e) {
            qDebug() << "Exception caught in StartupHandler::startUp: " << e.what();
            ptrObjectHandler = nullptr;
        }
        return ptrObjectHandler;
    }

    void StartupHandler::installTranslator() {
        QSharedPointer <QTranslator> translator = initTranslator();
        if (ptrApplication->installTranslator(translator.data())) {
            qDebug() << "Translator installed";
        }
    }

    QSharedPointer <QTranslator> StartupHandler::initTranslator() {
        QSharedPointer <QTranslator> translator(new QTranslator());
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

    QSharedPointer <ObjectHandler> StartupHandler::initObjectHandler() {
        QScopedPointer <DatabaseHandler> dbHandler(new DatabaseHandler());
        QScopedPointer <TableHandler> tableHandler(new TableHandler());
        if (dbHandler == nullptr || tableHandler == nullptr) {
            throw std::runtime_error("Failed to initialize DatabaseHandler or TableHandler");
        }
        return QSharedPointer<ObjectHandler>(new ObjectHandler(ptrApplication.data(), dbHandler.data(), tableHandler.data()));
    }

}