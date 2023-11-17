#pragma once

#include "launcherwindow.hpp"
#include "devwindow.hpp"
#include "../backendClasses/objecthandler.hpp"
#include "settingswindow.hpp"
#include <QObject>

class WindowHandler : public QObject
{
public:
    WindowHandler(ObjectHandler* newObjectHandler);


public slots:
    void showLaunchWindow();

private slots:
    void showDevWindow();
    void showSettingsWindow();
    void applySettings();

private:

    void changeLanguages();


    LauncherWindow *launcherWindow = nullptr;
    DevWindow *devWindow = nullptr;
    SettingsWindow *settingsWindow = nullptr;
    ObjectHandler *objectHandler;

};

