#include "OperatingWindow.h"
#include "ui_operatingwindow.h"
#include "AddNewAbonement.h"
#include <QDate>
#include <QMessageBox>

OperatingWindow::OperatingWindow(const bool read_from_file, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OperatingWindow)
{
    ui->setupUi(this);
    setToolTips();
    ui->centralwidget->setContextMenuPolicy(Qt::CustomContextMenu);
    QRegExpValidator* duration_per_day_validator = new QRegExpValidator(QRegExp("[+]?\\d*[\\.]?\\d+"));
    auto visits_validator = new QIntValidator(1,31);
    auto name_validator = new QRegExpValidator( QRegExp( "[А-і-І-я]{1,40}[ А-і-І-я]{1,40}[ А-і-І-я]{1,40}" )) ;
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
    try
    {
        HasData();
        CheckTableOutput();
    }
    catch(std::exception& except)
    {
        QMessageBox::information(this, "Warning", except.what());
        return;
    }
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
    try
    {
        std::ifstream file(FILE_NAME);
        if(!file.is_open())
            throw Exception("File is not opened\n");
        while(file.peek() != EOF)
        {
            SwimmingPoolSeasonTicket season_ticket;
            file >> season_ticket;
            m_season_tickets.push_back(season_ticket);
        }
        file.close();
   }
   catch(std::exception& except)
   {
       QMessageBox::critical(this, "Error", except.what());
   }

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
    try
    {
        HasData();
        CheckTableOutput();
    }
    catch(std::exception& except)
    {
        QMessageBox::information(this, "Warning", except.what());
        return;
    }
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
    try
    {
        HasData();
    }
    catch(std::exception& except)
    {
        QMessageBox::information(this, "Warning", except.what());
        return;
    }
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
    try
    {
        HasData();
    }
    catch(std::exception& except)
    {
        QMessageBox::information(this, "Warning", except.what());
        return;
    }
    auto current_date = QDate::currentDate().toString("dd.MM.yyyy").toStdString();
    Date today;
    today.SetDataFromStr(current_date);
    ui->MainTableWidget->clear();
    ui->MainTableWidget->setRowCount(0);
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    int row = 0;
    for(const auto& i : m_season_tickets)
    {
        if(i.get_additional_services().find(AdditionalServices::water_park) != i.get_additional_services().end())
        {
            if(i.get_end_date().m_year - today.m_year == 0)
            {
                    if( i.get_end_date().m_month - today.m_month == 0)
                {
                    UpdateTable(i, row++);
                }
                    else if(i.get_end_date().m_month - today.m_month == 1
                            && i.get_end_date().m_day - today.m_day <= 0)
                    {
                        UpdateTable(i, row++);
                    }
            }
            else if(i.get_end_date().m_year - today.m_year == 1)
            {
                if(i.get_end_date().m_month == 1 && today.m_month == 12
                          && i.get_end_date().m_day - today.m_day <= 0)
                  {
                      UpdateTable(i, row++);
                  }
            }
        }
    }
}

void OperatingWindow::on_PushButtonMaxVisitsPerMonthAndFamily_clicked()
{
    try
    {
        HasData();
    }
    catch(std::exception& except)
    {
        QMessageBox::information(this, "Warning", except.what());
        return;
    }
    auto max_visits_and_family_type = m_season_tickets.end();
    for(auto i = m_season_tickets.begin(); i != m_season_tickets.end(); ++i)
    {
        if(max_visits_and_family_type == m_season_tickets.end() && i->IsFamilyType())
        {
            max_visits_and_family_type = i;
            continue;
        }
        if(i->get_visits_per_month() > max_visits_and_family_type->get_visits_per_month()
                && i->IsFamilyType())
        {
            max_visits_and_family_type = i;
        }
    }

    ui->MainTableWidget->clear();
    ui->MainTableWidget->setRowCount(0);
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    if(max_visits_and_family_type == m_season_tickets.end())
    {
        QMessageBox::information(this, "Warning", "There is no abonement with such criteries");
        return;
    }
    UpdateTable(*max_visits_and_family_type, 0);
}

void OperatingWindow::on_PushButtonFindMaxAdditionalServicesAndMinDurationPerDay_clicked()
{
    try
    {
        HasData();
    }
    catch(std::exception& except)
    {
        QMessageBox::information(this, "Warning", except.what());
        return;
    }
    auto max_additional_services_and_min_duration = m_season_tickets.end();
    int max_additional_services = 0;
    for(auto i = m_season_tickets.begin(); i != m_season_tickets.end(); ++i)
    {
        if(static_cast<int>(i->get_additional_services().size()) > max_additional_services)
        {
            max_additional_services_and_min_duration = i;
            max_additional_services = static_cast<int>(i->get_additional_services().size());
        }
        else if(static_cast<int>(i->get_additional_services().size()) == max_additional_services
                && i->get_duration_per_day() < max_additional_services_and_min_duration->get_duration_per_day())
        {
            max_additional_services_and_min_duration = i;
        }
    }

    ui->MainTableWidget->clear();
    ui->MainTableWidget->setRowCount(0);
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    UpdateTable(*max_additional_services_and_min_duration, 0);
}

void OperatingWindow::on_PushButtonFindByName_clicked()
{
    try
    {
        HasData();
    }
    catch(std::exception& except)
    {
        QMessageBox::information(this, "Warning", except.what());
        return;
    }
    std::string name_to_find = ui->LineEditFindByName->text().toStdString();
    ui->MainTableWidget->clear();
    ui->MainTableWidget->setRowCount(0);
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    int row = 0;
    for(const auto& i : m_season_tickets)
    {
        std::string name = i.get_last_name() + " " + i.get_first_name() + " " + i.get_fathers_name();
        if(name.find(name_to_find) != std::string::npos)
        {
            UpdateTable(i ,row++);
        }
    }
}

void OperatingWindow::on_PushButtonFindByDuration_clicked()
{
    try
    {
        HasData();
    }
    catch(std::exception& except)
    {
        QMessageBox::information(this, "Warning", except.what());
        return;
    }
    auto duration_to_find = ui->LineEditFindByDuration->text().toDouble();
    ui->MainTableWidget->clear();
    ui->MainTableWidget->setRowCount(0);
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
    try
    {
        HasData();
    }
    catch(std::exception& except)
    {
        QMessageBox::information(this, "Warning", except.what());
        return;
    }
    auto visits_to_find = ui->LineEditFindByVisits->text().toInt();
    ui->MainTableWidget->clear();
    ui->MainTableWidget->setRowCount(0);
    QStringList horizontal_headers {"Прізвище", "Ім'я", "По-батькові", "Дата завершення", "Годин/день", "Відвідувань/місяць", "Сімейний"};
    ui->MainTableWidget->setHorizontalHeaderLabels(horizontal_headers);
    int row = 0;
    for(const auto& i : m_season_tickets)
    {
        if(static_cast<int>(i.get_visits_per_month()) == visits_to_find)
        {
            UpdateTable(i ,row++);
        }
    }
}

void OperatingWindow::on_centralwidget_customContextMenuRequested()
{
    QMenu* menu = new QMenu(ui->centralwidget);
    menu->addAction("Зберегти", this, [this](){this->on_PushButtonSaveDataToFile_clicked();});
    menu->addAction("Скинути фільтри", this, [this](){this->UpdateTable();});
    menu->exec(cursor().pos());
}

void OperatingWindow::CheckTableOutput() const
{
    if(ui->MainTableWidget->rowCount() != static_cast<int>(m_season_tickets.size()))
    {
        throw Exception("There is not all season tickets on the table\n");
    }
}
void OperatingWindow::HasData() const
{
    if(!m_season_tickets.size())
    {
        throw Exception("There is no season ticket to  operate with\n");
    }
}
void OperatingWindow::setToolTips()
{
    ui->PushButtonAddNew->setToolTip("Opens new window to add new season ticket");
    ui->PushButtonDeleteAbonemet->setToolTip("Deletes season ticket on specified row");
    ui->PushButtonFIndAdditionalServices->setToolTip("Shows additional services of specified season ticket");
    ui->PushButtonFindByDuration->setToolTip("Shows all season tickets with specified duration per day");
    ui->PushButtonFindByName->setToolTip("Shows all season tickets with specified name");
    ui->PushButtonFindMaxAdditionalServicesAndMinDurationPerDay->setToolTip("Shows season ticket with max amount of "
                                                                            "\nadditional services and min duration per day");
    ui->PushButtonLessThanMonthDurationAndHasWaterpark->setToolTip("Shows season tickets with duration less than a month"
                                                                   "\nand wich has water park additional service");
    ui->PushButtonMaxVisitsPerMonthAndFamily->setToolTip("Shows season ticket which has max visits per month and also is family type");
    ui->PushButtonSaveAdditionalServices->setToolTip("Saves additional services of specified season ticket");
    ui->PushButtonSaveDataToFile->setToolTip("Saves season tickets to \"waterpark.dat\"");
    ui->PushButtonfindByVisits->setToolTip("Show season tickets with specified amount of visits");
}

void OperatingWindow::on_actionSave_triggered()
{
    SaveDataToFile();
}

void OperatingWindow::on_actionUpload_table_triggered()
{
    UpdateTable();
}

void OperatingWindow::on_actionInfo_triggered()
{
    QMessageBox message_box;
    message_box.setText(R"(Варіант 8
                        Створити клас «Абонемент в басейн» (ПІП, період дії картки, тривалість перебування в день,
                        кількість відвідувань в місяць, сімейний (bool), масив додаткових послуг). Для класу
                        створити: 1) конструктор за замовчуванням; 2) конструктор з параметрами; 3) конструктор
                        копій; 4) перевизначити операції >> << для зчитування та запису у файл.
                        Наповнити клас даними, прочитавши відповідний файл waterpark.dat.
                        Реалізувати:
                        1) функції пошуку за ПІП, тривалістю перебування, за вказаною кількістю відвідувань, за
                        тривалістю перебування.
                        2) функцію додавання даних у масив додаткових послуг (сауна, аквапарк, масаж, тощо).
                        3) Вивести інформацію про абонемент, в якого закінчується період дії картки (менше 1
                        місяця) та містить додаткову послугу аквапарк одночасно.
                        4) Вивести інформацію про абонемент, в якого найбільше додаткових послуг та
                        найменша тривалість перебування в день.
                        5) Вивести інформацію про абонемент, що має найбільшу кількість відвідувань в місяць
                        та є сімейним одночасно.
                        Для демонстрації роботи програми використати засоби візуального середовища
                        програмування.)");
    message_box.exec();
}
