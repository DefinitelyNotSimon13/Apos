#include "launcherwindow.hpp"
#include "ui_launcherwindow.h"

LauncherWindow::LauncherWindow(QWidget *parent, ObjectHandler* newObjectHandler) :
    QMainWindow(parent),
    ui(new Ui::LauncherWindow)
{
    ui->setupUi(this);
    objectHandler = newObjectHandler;

}

LauncherWindow::~LauncherWindow()
{
    delete ui;
}


void LauncherWindow::on_inShowDev_clicked()
{
    emit openDevWindow();
}




void LauncherWindow::on_pushButton_clicked()
{
    emit openSettings();
}

void LauncherWindow::retranslateUi()
{

}

