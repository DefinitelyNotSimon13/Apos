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
    SettingsWindow::SettingsWindow(QWidget *parent, QSharedPointer<AposBackend::ObjectHandler> newObjectHandler) :
            QWidget(parent),
            ui(new Ui::SettingsWindow) {
        ui->setupUi(this);
        ptrObjectHandler = std::move(newObjectHandler);
        ptrTranslator = QSharedPointer<QTranslator>(new QTranslator);
        settingsConnectUi();
    }

    SettingsWindow::~SettingsWindow() {
        delete ui;
    }

    void SettingsWindow::settingsConnectUi() {
        //TODO: implement Logger
        connect(ui->inClose, SIGNAL(clicked()), this, SLOT(closeClicked()));
        connect(ui->inApply, SIGNAL(clicked()), this, SLOT(applyClicked()));
        connect(ui->inLanguage, SIGNAL(currentIndexChanged(int)), this, SLOT(languageCurrentIndexChanged(int)));
    }

    void SettingsWindow::retranslateUi() {
        ui->retranslateUi(this);
    }

    void SettingsWindow::closeClicked() {
        this->hide();
    }


    void SettingsWindow::applyClicked() {
        if (languageChanged) {
            qDebug() << "New Language will be applied";

            languageIndex = tempLanguageIndex;
            installTranslator();
        }
        emit appliedSettings();
    }


    void SettingsWindow::languageCurrentIndexChanged(int index) {
        tempLanguageIndex = index;
        qDebug() << "checkboxIndex: " << index << "tempIndex: " << tempLanguageIndex << "index: " << languageIndex;
        if (tempLanguageIndex == languageIndex) {
            qDebug() << "Language not changed";
            languageChanged = false;
            return;
        }
        qDebug() << "Language changed";
        languageChanged = true;
    }

    void SettingsWindow::installTranslator() {
        qDebug() << "Language Index: " << languageIndex;

        QTranslator *translator = ptrTranslator.data();
        if(ptrObjectHandler->getPtrApplication()->removeTranslator(translator)){
            qDebug() << "removed translator";
        }
        else{
            qDebug() << "could not remove translator";
        }
        ptrTranslator = QSharedPointer<QTranslator>(new QTranslator);
        switch (languageIndex) {
            case 0:
                (void)ptrTranslator->load(":/i18n/Apos-DatabaseManager_en_GB");
                qDebug() << "tried to load english";
                translator = ptrTranslator.data();
                (void)ptrObjectHandler->getPtrApplication()->installTranslator(translator);
                break;
            case 1:
                (void)ptrTranslator->load(":/i18n/Apos-DatabaseManager_de_DE");
                qDebug() << "tried to load german";
                translator = ptrTranslator.data();
                (void)ptrObjectHandler->getPtrApplication()->installTranslator(translator);
                break;
            default:
                qDebug() << "no language selected";
                break;
        }
    }
}
