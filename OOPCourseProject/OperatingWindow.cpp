#include "OperatingWindow.h"
#include "ui_operatingwindow.h"
#include "AddNewAbonement.h"
#include <QDate>

OperatingWindow::OperatingWindow(const bool read_from_file, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OperatingWindow)
{
    ui->setupUi(this);
    QRegExpValidator* duration_per_day_validator = new QRegExpValidator(QRegExp("[+]?\\d*[\\.]?\\d+"));
    auto visits_validator = new QIntValidator(1,31);
    auto name_validator = new QRegExpValidator( QRegExp( "[А-і-І-я]{1,40}" )) ;
    ui->LineEditFindByName->setValidator(name_validator);
    ui->LineEditFindByVisits->setValidator(visits_validator);
    ui->LineEditFindByDuration->setValidator(duration_per_day_validator);
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
    ui->LineEditNumberToFindAdditionalServices->setValidator(operations_index_validator);
    ui->LineEditNumToOperate->setValidator(operations_index_validator);
}

OperatingWindow::~OperatingWindow()
{
    delete ui;
}

void OperatingWindow::UpdateTable()
{
    ui->MainTableWidget->setRowCount(static_cast<int>(m_season_tickets.size()));
    auto operations_index_validator = new QIntValidator(1, static_cast<int>(m_season_tickets.size()));
    ui->LineEditNumberToFindAdditionalServices->setValidator(operations_index_validator);
    ui->LineEditNumToOperate->setValidator(operations_index_validator);
    int row_index = 0;
    for(auto& i : m_season_tickets)
    {
        UpdateTable(i ,row_index);
        ++row_index;
    }
}
void OperatingWindow::UpdateTable(const SwimmingPoolSeasonTicket& season_ticket, const int row)
{
    if(ui->MainTableWidget->rowCount() - 1 < row)
    {
        ui->MainTableWidget->setRowCount(row + 1);
    }
    int column_index = 0;
    auto last_name_item = new QTableWidgetItem(QString(season_ticket.get_last_name().c_str()));
    ui->MainTableWidget->setItem(row, column_index++, last_name_item);
    auto first_name_item = new QTableWidgetItem(QString(season_ticket.get_first_name().c_str()));
    ui->MainTableWidget->setItem(row, column_index++, first_name_item);
    auto fathers_name_item = new QTableWidgetItem(QString(season_ticket.get_fathers_name().c_str()));
    ui->MainTableWidget->setItem(row, column_index++, fathers_name_item);
    auto end_date_item =  new QTableWidgetItem(QString(season_ticket.get_end_date().DataToStr().c_str()));
    ui->MainTableWidget->setItem(row, column_index++, end_date_item);
    auto duration_per_day_item = new QTableWidgetItem(QString::number(season_ticket.get_duration_per_day()));
    ui->MainTableWidget->setItem(row, column_index++, duration_per_day_item);
    auto visits_per_month_item = new QTableWidgetItem(QString::number(season_ticket.get_visits_per_month()));
    ui->MainTableWidget->setItem(row, column_index++, visits_per_month_item);
    auto is_family_item = new QTableWidgetItem(season_ticket.IsFamilyType() ? "Так" : "Ні");
    ui->MainTableWidget->setItem(row, column_index++, is_family_item);
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

void OperatingWindow::on_PushButtonDeleteAbonemet_clicked()
{
    ui->TableWidgetAdditionalServices->clear();
    int element_index;
    if(ui->LineEditNumToOperate->hasAcceptableInput())
    {
        element_index = ui->LineEditNumToOperate->text().toInt() - 1;
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

void OperatingWindow::on_PushButtonFIndAdditionalServices_clicked()
{
    ui->TableWidgetAdditionalServices->clear();
    int element_index;
    if(ui->LineEditNumberToFindAdditionalServices->hasAcceptableInput())
    {
        element_index = ui->LineEditNumberToFindAdditionalServices->text().toInt() - 1;
    }
    else
    {
        return;
    }
    auto processed_element = m_season_tickets.begin();
    std::advance(processed_element, element_index);
    auto additional_services = processed_element->get_additional_services();
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

void OperatingWindow::on_PushButtonSaveAdditionalServices_clicked()
{
    int element_index;
    if(ui->LineEditNumberToFindAdditionalServices->hasAcceptableInput())
    {
        element_index = ui->LineEditNumberToFindAdditionalServices->text().toInt() - 1;
    }
    else
    {
        return;
    }
    auto processed_element = m_season_tickets.begin();
    std::advance(processed_element, element_index);
    std::set<AdditionalServices> additional_services {};
    int row_index = 0;
    if(ui->TableWidgetAdditionalServices->item(row_index++, 0)->text() == "Так")
    {
        additional_services.emplace(AdditionalServices::gym);
    }
    if(ui->TableWidgetAdditionalServices->item(row_index++, 0)->text() == "Так")
    {
        additional_services.emplace(AdditionalServices::massage);
    }
    if(ui->TableWidgetAdditionalServices->item(row_index++, 0)->text() == "Так")
    {
        additional_services.emplace(AdditionalServices::sauna);
    }
    if(ui->TableWidgetAdditionalServices->item(row_index++, 0)->text() == "Так")
    {
        additional_services.emplace(AdditionalServices::steam_room);
    }
    if(ui->TableWidgetAdditionalServices->item(row_index++, 0)->text() == "Так")
    {
        additional_services.emplace(AdditionalServices::water_park);
    }
    processed_element->set_additional_services(additional_services);
}

void OperatingWindow::on_PushButtonLessThanMonthDurationAndHasWaterpark_clicked()
{
    auto current_date = QDate::currentDate().toString("dd.MM.yyyy").toStdString();
    Date today;
    today.SetDataFromStr(current_date);
    ui->MainTableWidget->clear();
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    int row = 0;
    for(const auto& i : m_season_tickets)
    {
        if(i.get_end_date().m_year - today.m_year == 0
                && i.get_end_date().m_month - today.m_month == 0
                && i.get_additional_services().find(AdditionalServices::water_park) != i.get_additional_services().end())
        {
            UpdateTable(i, row++);
        }
    }
}

void OperatingWindow::on_PushButtonMaxVisitsPerMonthAndFamily_clicked()
{
    SwimmingPoolSeasonTicket max_visits_and_family_type;
    max_visits_and_family_type.set_visits_per_month(0);
    for(const auto& i : m_season_tickets)
    {
        if(i.get_visits_per_month() > max_visits_and_family_type.get_visits_per_month()
                && i.IsFamilyType())
        {
            max_visits_and_family_type = i;
        }
    }

    ui->MainTableWidget->clear();
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    UpdateTable(max_visits_and_family_type, 0);
}

void OperatingWindow::on_PushButtonFindMaxAdditionalServicesAndMinDurationPerDay_clicked()
{
    SwimmingPoolSeasonTicket max_additional_services_and_min_duration;
    int max_additional_services = 0;
    for(const auto& i : m_season_tickets)
    {
        if(i.get_additional_services().size() > max_additional_services)
        {
            max_additional_services_and_min_duration = i;
            max_additional_services = static_cast<int>(i.get_additional_services().size());
        }
        else if(i.get_additional_services().size() == max_additional_services
                && i.get_duration_per_day() < max_additional_services_and_min_duration.get_duration_per_day())
        {
            max_additional_services_and_min_duration = i;
        }
    }

    ui->MainTableWidget->clear();
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    UpdateTable(max_additional_services_and_min_duration, 0);
}

void OperatingWindow::on_PushButtonFindByName_clicked()
{
    std::string name_to_find = ui->LineEditFindByName->text().toStdString();
    ui->MainTableWidget->clear();
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    int row = 0;
    for(const auto& i : m_season_tickets)
    {
        if(i.get_first_name().find(name_to_find) != std::string::npos
                || i.get_last_name().find(name_to_find) != std::string::npos
                || i.get_fathers_name().find(name_to_find) != std::string::npos)
        {
            UpdateTable(i ,row++);
        }
    }
}

void OperatingWindow::on_PushButtonFindByDuration_clicked()
{
    auto duration_to_find = ui->LineEditFindByDuration->text().toDouble();
    ui->MainTableWidget->clear();
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    int row = 0;
    for(const auto& i : m_season_tickets)
    {
        if(i.get_duration_per_day() == duration_to_find)
        {
            UpdateTable(i ,row++);
        }
    }
}

void OperatingWindow::on_PushButtonfindByVisits_clicked()
{
    auto visits_to_find = ui->LineEditFindByVisits->text().toInt();
    ui->MainTableWidget->clear();
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    int row = 0;
    for(const auto& i : m_season_tickets)
    {
        if(i.get_visits_per_month() == visits_to_find)
        {
            UpdateTable(i ,row++);
        }
    }
}



