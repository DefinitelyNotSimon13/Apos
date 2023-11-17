#include "windowhandler.hpp"
#include "translatablewindow.hpp"


WindowHandler::WindowHandler(ObjectHandler *newObjectHandler)
{

    objectHandler = newObjectHandler;
    launcherWindow = new LauncherWindow(nullptr, objectHandler);
    settingsWindow = new SettingsWindow();
    QObject::connect(launcherWindow, &LauncherWindow::openDevWindow, this, &WindowHandler::showDevWindow, Qt::DirectConnection);
    QObject::connect(launcherWindow, &LauncherWindow::openSettings, this, &WindowHandler::showSettingsWindow);
    QObject::connect(settingsWindow, &SettingsWindow::appliedSettings, this, &WindowHandler::applySettings);

}

void WindowHandler::showLaunchWindow()
{
    if (devWindow != nullptr){
        if (!devWindow->isHidden()){
            devWindow->hide();
        }
    }
    launcherWindow->show();
}

void WindowHandler::showDevWindow()
{
    launcherWindow->hide();
    if(devWindow == nullptr){
        devWindow = new DevWindow(nullptr, objectHandler);
        QObject::connect(devWindow, &DevWindow::returnToLauncher, this, &WindowHandler::showLaunchWindow, Qt::DirectConnection);
        QObject::connect(devWindow, &DevWindow::openSettings, this, &WindowHandler::showSettingsWindow, Qt::DirectConnection);
    }

    devWindow->show();
}

void WindowHandler::showSettingsWindow()
{
    settingsWindow->show();
}

void WindowHandler::applySettings()
{
    changeLanguages();
}

void WindowHandler::changeLanguages()
{
    QWidgetList openWindows = objectHandler->application->topLevelWidgets();
    for(QWidget *widget : qAsConst(openWindows)){
        TranslatableWindow *tw = dynamic_cast<TranslatableWindow*>(widget);
        if(tw){
            qDebug() << "Dynamic cast pointer adress " << tw;
            tw->retranslateUi();
        }
    }
    qDebug() << openWindows;
}
