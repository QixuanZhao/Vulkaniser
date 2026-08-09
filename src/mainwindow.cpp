#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UI/About/AboutWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::process(QAction *action)
{
    if (action == ui->actionInfo) {
        AboutWindow *aboutWindow = new AboutWindow(this);
        aboutWindow->open();
    }
}