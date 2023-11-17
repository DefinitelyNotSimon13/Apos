#include "settingswindow.hpp"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent, ObjectHandler *newObjectHandler) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    objectHandler = newObjectHandler;
    translator = new QTranslator;
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::retranslateUi()
{
    ui->retranslateUi(this);
}

void SettingsWindow::on_inClose_clicked()
{
    this->hide();
}


void SettingsWindow::on_inApply_clicked()
{
    if(languageChanged){
        qDebug() << "New Language will be applied";

        languageIndex = tempLanguageIndex;
        installTranslator();
    }
    emit appliedSettings();
}


void SettingsWindow::on_inLanguage_currentIndexChanged(int index)
{
    tempLanguageIndex = index;
    qDebug() << "checkboxIndex: " << index << "tempIndex: " << tempLanguageIndex << "index: " << languageIndex;
    if(tempLanguageIndex == languageIndex){
        qDebug() << "Language not changed";
        languageChanged = false;
        return;
    }
    qDebug() << "Language changed";
    languageChanged = true;
}

void SettingsWindow::installTranslator()
{
    qDebug() << languageIndex;
    objectHandler->application->removeTranslator(translator);
    delete translator;
    translator = new QTranslator;
    switch (languageIndex){
    case 0:
        translator->load(":/i18n/Apos-DatabaseManager_en_GB");
        qDebug() << "tried to load english";
        objectHandler->application->installTranslator(translator);
        break;
    case 1:
        translator->load(":/i18n/Apos-DatabaseManager_de_DE");
        qDebug() << "tried to load german";
        objectHandler->application->installTranslator(translator);
        break;
    }
}

