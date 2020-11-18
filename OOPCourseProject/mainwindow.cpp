#include <QAction>

#include "mainwindow.h"
#include "OperatingWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setContextMenuPolicy(Qt::ActionsContextMenu);
        QAction* copy = new QAction("Скопіювати");
        QAction* paste = new QAction("Вставити");
        connect(copy, SIGNAL(triggered()), this, SLOT(copy_to_clipboard()));
        connect(paste, SIGNAL(triggered()), this, SLOT(paste_to_browser()));
        ui->centralwidget->addActions({ copy, paste });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PushButtonOpenFile_clicked()
{
    OperatingWindow *window = new OperatingWindow;
    window->show();
    close();
}

void MainWindow::on_PushButtonContinueWithoutFile_clicked()
{
    OperatingWindow *window = new OperatingWindow;
    window->show();
    close();
}
