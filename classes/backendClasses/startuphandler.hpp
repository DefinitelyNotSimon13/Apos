#pragma once

#include <QDebug>
#include <QtSql>
#include <QLocale>
#include <QTranslator>

#include "objecthandler.hpp"


class StartupHandler
{
public:


    StartupHandler(QApplication* application);

    ~StartupHandler();


    ObjectHandler* startUp();


private:


    void initTranslator();

    void initObjectHandler();



    QApplication *ptrApplication; /**< The QApplication instance. */

    ObjectHandler *objectHandler; /**< The ObjectHandler instance. */
};

