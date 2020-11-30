#include "OperatingWindow.h"
#include "ui_operatingwindow.h"
#include "AddNewAbonement.h"

OperatingWindow::OperatingWindow(const bool read_from_file, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OperatingWindow)
{
    ui->setupUi(this);

    //ui->MainTableWidget->setRowCount(m_season_tickets.size());
    ui->MainTableWidget->setColumnCount(DEFAULT_COLUMN_COUNT);
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    ui->TableWidgetAdditionalServices->setRowCount(5);
    ui->TableWidgetAdditionalServices->setColumnCount(1);
    ui->TableWidgetAdditionalServices->setHorizontalHeaderLabels(QStringList("Включено"));
    QStringList vertical_headers {"Зал", "Масаж", "Сауна", "Парна", "Аквапарк"};
    ui->TableWidgetAdditionalServices->setVerticalHeaderLabels(vertical_headers);
    if(read_from_file)
    {
        ReadDataFromFile();
    }
    UpdateTable();

    auto operations_index_validator = new QIntValidator(1, static_cast<int>(m_season_tickets.size()));
    ui->LineEditNumberToFind->setValidator(operations_index_validator);
    ui->LineEditNumToDelete->setValidator(operations_index_validator);
}

OperatingWindow::~OperatingWindow()
{
    delete ui;
}

void OperatingWindow::UpdateTable()
{
    ui->MainTableWidget->setRowCount(static_cast<int>(m_season_tickets.size()));
    auto operations_index_validator = new QIntValidator(1, static_cast<int>(m_season_tickets.size()));
    ui->LineEditNumberToFind->setValidator(operations_index_validator);
    ui->LineEditNumToDelete->setValidator(operations_index_validator);
    int row_index = 0;
    for(auto& i : m_season_tickets)
    {
        int column_index = 0;
        auto last_name_item = new QTableWidgetItem(QString(i.get_last_name().c_str()));
        ui->MainTableWidget->setItem(row_index, column_index++, last_name_item);
        auto first_name_item = new QTableWidgetItem(QString(i.get_first_name().c_str()));
        ui->MainTableWidget->setItem(row_index, column_index++, first_name_item);
        auto fathers_name_item = new QTableWidgetItem(QString(i.get_fathers_name().c_str()));
        ui->MainTableWidget->setItem(row_index, column_index++, fathers_name_item);
        auto end_date_item =  new QTableWidgetItem(QString(i.get_end_date().DataToStr().c_str()));
        ui->MainTableWidget->setItem(row_index, column_index++, end_date_item);
        auto duration_per_day_item = new QTableWidgetItem(QString::number(i.get_duration_per_day()));
        ui->MainTableWidget->setItem(row_index, column_index++, duration_per_day_item);
        auto visits_per_month_item = new QTableWidgetItem(QString::number(i.get_visits_per_month()));
        ui->MainTableWidget->setItem(row_index, column_index++, visits_per_month_item);
        auto is_family_item = new QTableWidgetItem(i.IsFamilyType() ? "Так" : "Ні");
        ui->MainTableWidget->setItem(row_index, column_index++, is_family_item);
        ++row_index;
    }
}

void OperatingWindow::on_PushButtonAddNew_clicked()
{
    SwimmingPoolSeasonTicket new_season_ticket;
    AddNewAbonement* add_new_abonement_window = new AddNewAbonement(new_season_ticket, this);
    add_new_abonement_window->exec();
    if(!new_season_ticket.Empty())
        m_season_tickets.emplace_back(new_season_ticket);
    UpdateTable();
}

void OperatingWindow::on_PushButtonFIndAbonement_clicked()
{
    ui->TableWidgetAdditionalServices->clearContents();
    int element_index;
    if(ui->LineEditNumberToFind->hasAcceptableInput())
    {
        element_index = ui->LineEditNumberToFind->text().toInt() - 1;
    }
    else
    {
        return;
    }
    auto processed_elemet = m_season_tickets.begin();
    std::advance(processed_elemet, element_index);
    auto additional_services = processed_elemet->get_additional_services();
    if(additional_services.empty())
        return;
    int row_index = 0;
    if(additional_services.find(AdditionalServices::gym) != additional_services.end())
    {
        auto item = new QTableWidgetItem("Так");
        ui->TableWidgetAdditionalServices->setItem(row_index++, 0, item);
    }
    else
    {
        auto item = new QTableWidgetItem("Ні");
        ui->TableWidgetAdditionalServices->setItem(row_index++, 0, item);
    }
    if(additional_services.find(AdditionalServices::massage) != additional_services.end())
    {
        auto item = new QTableWidgetItem("Так");
        ui->TableWidgetAdditionalServices->setItem(row_index++, 0, item);
    }
    else
    {
        auto item = new QTableWidgetItem("Ні");
        ui->TableWidgetAdditionalServices->setItem(row_index++, 0, item);
    }
    if(additional_services.find(AdditionalServices::sauna) != additional_services.end())
    {
        auto item = new QTableWidgetItem("Так");
        ui->TableWidgetAdditionalServices->setItem(row_index++, 0, item);
    }
    else
    {
        auto item = new QTableWidgetItem("Ні");
        ui->TableWidgetAdditionalServices->setItem(row_index++, 0, item);
    }
    if(additional_services.find(AdditionalServices::steam_room) != additional_services.end())
    {
        auto item = new QTableWidgetItem("Так");
        ui->TableWidgetAdditionalServices->setItem(row_index++, 0, item);
    }
    else
    {
        auto item = new QTableWidgetItem("Ні");
        ui->TableWidgetAdditionalServices->setItem(row_index++, 0, item);
    }
    if(additional_services.find(AdditionalServices::water_park) != additional_services.end())
    {
        auto item = new QTableWidgetItem("Так");
        ui->TableWidgetAdditionalServices->setItem(row_index++, 0, item);
    }
    else
    {
        auto item = new QTableWidgetItem("Ні");
        ui->TableWidgetAdditionalServices->setItem(row_index++, 0, item);
    }
}

void OperatingWindow::on_PushButtonDeleteAbonemet_clicked()
{
    ui->TableWidgetAdditionalServices->clearContents();
    int element_index;
    if(ui->LineEditNumberToFind->hasAcceptableInput())
    {
        element_index = ui->LineEditNumberToFind->text().toInt() - 1;
    }
    else
    {
        return;
    }
    auto processed_elemet = m_season_tickets.begin();
    std::advance(processed_elemet, element_index);
    m_season_tickets.erase(processed_elemet);
    UpdateTable();
}

void OperatingWindow::on_PushButtonSaveDataToFile_clicked()
{
    SaveDataToFile();
}

void OperatingWindow::ReadDataFromFile()
{
    std::ifstream file(FILE_NAME);
    if(!file.is_open())
        throw std::runtime_error("File is not opened\n");
    try
    {
        while(file.peek() != EOF)
        {
            SwimmingPoolSeasonTicket season_ticket;
            file >> season_ticket;
            m_season_tickets.push_back(season_ticket);
        }
   }
   catch(std::exception &except)
   {
       //do something
   }
   file.close();
}
void OperatingWindow::SaveDataToFile() const
{
    std::ofstream file(FILE_NAME, std::ofstream::out | std::fstream::trunc);
    if(!file.is_open())
        throw std::runtime_error("File is not opened\n");
    for(auto i : m_season_tickets)
    {
        file << i;
    }
    file.close();
}




