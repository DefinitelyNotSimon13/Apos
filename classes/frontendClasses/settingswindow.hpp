#pragma once

#include <QWidget>
#include <QDebug>
#include "basicClasses/objecthandler.hpp"
#include "translatablewindow.hpp"
#include <QTranslator>


namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget, public TranslatableWindow
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr, ObjectHandler *objectHandler = nullptr);
    ~SettingsWindow();
    void retranslateUi();
signals:
    void appliedSettings();

private slots:
    void on_inClose_clicked();

    void on_inApply_clicked();

    void on_inLanguage_currentIndexChanged(int index);

private:

    void installTranslator();

    Ui::SettingsWindow *ui;
    QString language;
    ObjectHandler* objectHandler;
    QTranslator* translator;
    int languageIndex, tempLanguageIndex;
    bool languageChanged;
};

