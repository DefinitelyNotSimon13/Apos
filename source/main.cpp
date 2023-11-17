#include "../classes/backendClasses/startuphandler.hpp"
#include "../classes/backendClasses/objecthandler.hpp"
#include "../classes/frontendClasses/windowhandler.hpp"

#include <QApplication>
#include <QDebug>
#include <QtSql>


int main(int argc, char *argv[])
{
    QApplication *a = new QApplication(argc, argv);
    qDebug() << "Application Object initialized";

    StartupHandler startupHandler(a);
    qDebug() << "StartupHandler Object initialized";

    ObjectHandler *objectHandler = startupHandler.startUp();
    qDebug() << "ObjectHandler Object initialized";
    startupHandler.~StartupHandler();

    WindowHandler windowHandler(objectHandler);
    windowHandler.showLaunchWindow();

    qDebug() << "After DevWindow Show";

    return a->exec();
}
