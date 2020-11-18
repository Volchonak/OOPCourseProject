#include "OperatingWindow.h"
#include "ui_operatingwindow.h"
#include "AddNewAbonement.h"

OperatingWindow::OperatingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OperatingWindow)
{
    ui->setupUi(this);
    ui->MainTableWidget->setRowCount(0);
    ui->MainTableWidget->setColumnCount(7);
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    ui->TableWidgetAdditionalServices->setRowCount(5);
    ui->TableWidgetAdditionalServices->setColumnCount(1);
    ui->TableWidgetAdditionalServices->setHorizontalHeaderLabels(QStringList("Включено"));
    QStringList vertical_headers {"Сауна", "Аквапарк", "Масаж", "Зал", "Парна"};
    ui->TableWidgetAdditionalServices->setVerticalHeaderLabels(vertical_headers);
}

OperatingWindow::~OperatingWindow()
{
    delete ui;
}

void OperatingWindow::on_PushButtonAddNew_clicked()
{
    SwimmingPoolSeasonTicket new_season_ticket;
    AddNewAbonement* add_new_abonement_window = new AddNewAbonement(new_season_ticket);
    add_new_abonement_window->show();
    //add season ticket if it is valid
}
