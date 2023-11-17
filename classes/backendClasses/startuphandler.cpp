// Copyright (c) 2023. LGPL-V3
//

#include "startuphandler.hpp"

StartupHandler::StartupHandler(QApplication *application) {
    this->ptrApplication = application;
}

StartupHandler::~StartupHandler() {
    qDebug() << "StartupHandler deleted!";
}

ObjectHandler *StartupHandler::startUp() {

    initObjectHandler();
    initTranslator();
    return objectHandler;

}

void StartupHandler::initTranslator() {
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale: uiLanguages) {
        const QString baseName = "Apos-DatabaseManager_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            ptrApplication->installTranslator(&translator);
            break;
        }
    }
}

void StartupHandler::initObjectHandler() {
    DatabaseHandler *dbHandler = new DatabaseHandler();
    TableHandler *tableHandler = new TableHandler();
    objectHandler = new ObjectHandler(ptrApplication, dbHandler, tableHandler);
}

