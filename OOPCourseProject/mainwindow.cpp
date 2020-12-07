#include <QAction>

#include "mainwindow.h"
#include "OperatingWindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_PushButtonOpenFile_clicked()
{
    OperatingWindow *window = new OperatingWindow(true);
    window->show();
    close();
}

void MainWindow::on_PushButtonContinueWithoutFile_clicked()
{
    OperatingWindow *window = new OperatingWindow(false);
    window->show();
    close();
}

