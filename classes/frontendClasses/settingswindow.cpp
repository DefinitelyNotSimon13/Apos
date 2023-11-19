/**
 * @file settingswindow.cpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Source file for the SettingsWindow class.
 *
 * @details This file contains the implementation of the SettingsWindow class, which is a part of the application's frontend logic.
 * The SettingsWindow class inherits from QWidget and TranslatableWindow, and it provides the user interface for the settings window.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see AposBackend::ObjectHandler
 * @see TranslatableWindow
 * @see QWidget
 * @see QTranslator
 * @see QSharedPointer
 */
#include "settingswindow.hpp"

#include <utility>
#include "ui_settingswindow.h"


namespace AposFrontend {
    SettingsWindow::SettingsWindow(QWidget *parent, QSharedPointer<AposBackend::ObjectHandler> newObjectHandler,
                                   QSharedPointer<AposLogger::Logger> newLogger)
            : QWidget(parent),
              ptrObjectHandler(qMove(newObjectHandler)),
              ptrLogger(qMove(newLogger)),
              ui(new Ui::SettingsWindow) {
        ui->setupUi(this);
        ptrTranslator = QSharedPointer<QTranslator>(new QTranslator);
        settingsConnectUi();
        ptrLogger->log("init", "SettingsWindow initialized and connected to UI");
    }

    SettingsWindow::~SettingsWindow() {
        delete ui;
        ptrLogger->log("status", "SettingsWindow destroyed");
    }

    void SettingsWindow::settingsConnectUi() {
        connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(closeClicked()));
        connect(ui->btnApply, SIGNAL(clicked()), this, SLOT(applyClicked()));
        connect(ui->btnApplyAndClose, SIGNAL(clicked()), this, SLOT(applyAndCloseClicked()));
        connect(ui->inLanguage, SIGNAL(currentIndexChanged(int)), this, SLOT(languageCurrentIndexChanged(int)));
    }

    void SettingsWindow::retranslateUi() {
        ui->retranslateUi(this);
        ptrLogger->log("status", "SettingsWindow retranslated");
    }

    void SettingsWindow::closeClicked() {
        this->hide();
        ptrLogger->log("signal", "SettingsWindow hidden");
    }


    void SettingsWindow::applyClicked() {
        if (languageChanged) {
            ptrLogger->log("signal", "New language will be applied!");

            languageIndex = tempLanguageIndex;
            installTranslator();
        }
        ptrLogger->log("signal", "Settings applied sent");
        emit appliedSettings();
    }

    void SettingsWindow::applyAndCloseClicked() {
        applyClicked();
        closeClicked();
    }


    void SettingsWindow::languageCurrentIndexChanged(int index) {
        tempLanguageIndex = index;
        if (tempLanguageIndex == languageIndex) {
            languageChanged = false;
            return;
        }
        ptrLogger->log("status", "Language index changed");
        languageChanged = true;
    }

    void SettingsWindow::installTranslator() {
        ptrLogger->log("status", "Language index: " + QString::number(languageIndex));

        QTranslator *translator = ptrTranslator.data();
        if (ptrObjectHandler->getPtrApplication()->removeTranslator(translator)) {
            ptrLogger->log("status", "Translator removed");
        } else {
            ptrLogger->log("error", "Translator not removed");
        }
        ptrTranslator = QSharedPointer<QTranslator>(new QTranslator);
        switch (languageIndex) {
            case 0:
                if (ptrTranslator->load(":/i18n/Apos-DatabaseManager_en_GB")) {
                    ptrLogger->log("status", "loaded english");
                } else {
                    ptrLogger->log("error", "couldn't load english");
                }
                translator = ptrTranslator.data();
                if (ptrObjectHandler->getPtrApplication()->installTranslator(translator)) {
                    ptrLogger->log("status", "Translator installed");
                } else {
                    ptrLogger->log("error", "Translator not installed");
                }
                break;
            case 1:
                if (ptrTranslator->load(":/i18n/Apos-DatabaseManager_de_DE")) {
                    ptrLogger->log("status", "loaded german");
                } else {
                    ptrLogger->log("error", "couldn't load german");
                }
                qDebug() << "tried to load german";
                translator = ptrTranslator.data();
                if (ptrObjectHandler->getPtrApplication()->installTranslator(translator)) {
                    ptrLogger->log("status", "Translator installed");
                } else {
                    ptrLogger->log("error", "Translator not installed");
                }
                break;
            default:
                ptrLogger->log("error", "Language index not found");
                break;
        }
    }
}
