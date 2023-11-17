// Copyright (c) 2023. LGPL-V3
//

#pragma once

#include <QMainWindow>

#include "../backendClasses/objecthandler.hpp"
#include "translatablewindow.hpp"

namespace Ui {
    class LauncherWindow;
}

class LauncherWindow : public QMainWindow, public TranslatableWindow {
Q_OBJECT

public:
    explicit LauncherWindow(QWidget *parent = nullptr, ObjectHandler *newObjectHandler = nullptr);

    ~LauncherWindow();

    Ui::LauncherWindow *ui;

    void retranslateUi();

signals:

    void openDevWindow();

    void openSettings();

private slots:

    void on_inShowDev_clicked();

    void on_pushButton_clicked();

private:

    ObjectHandler *objectHandler;
};

