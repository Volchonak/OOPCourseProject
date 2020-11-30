#include "AddNewAbonement.h"
#include "ui_AddNewAbonement.h"
#include "QValidator"
#include "QList"
#include "OperatingWindow.h"

AddNewAbonement::AddNewAbonement(SwimmingPoolSeasonTicket& season_ticket, QWidget *parent) :
    QDialog(parent)
    ,ui(new Ui::AddNewAbonement)
    ,m_season_ticket(season_ticket)
{
    ui->setupUi(this);
    auto day_validator = new QIntValidator(1,31);
    auto month_validator = new QIntValidator(1,12);
    auto year_validator = new QIntValidator(2019,2400);
    QRegExpValidator* duration_per_day_validator = new QRegExpValidator(QRegExp("[+]?\\d*[\\.]?\\d+"));
    auto name_validator = new QRegExpValidator( QRegExp( "[А-і-І-я]{1,40}" )) ;
    ui->LineEditLastName->setPlaceholderText("Прізвище");
    ui->LineEditLastName->setValidator(name_validator);
    ui->LineEditFirstName->setPlaceholderText("Ім'я");
    ui->LineEditFirstName->setValidator(name_validator);
    ui->LineEditFathersName->setPlaceholderText("По-батькові");
    ui->LineEditFathersName->setValidator(name_validator);
    ui->LineEditDurationPerDay->setPlaceholderText("Тривалість перебування в день");
    ui->LineEditDurationPerDay->setValidator(duration_per_day_validator);
    ui->LineEditVisitsPerMonth->setPlaceholderText("К-сть відвідувань у місяць");
    ui->LineEditVisitsPerMonth->setValidator(day_validator);
    ui->LineEditEndDay->setPlaceholderText("День завершення");
    ui->LineEditEndDay->setValidator(day_validator);
    ui->LineEditEndMonth->setPlaceholderText("Місяць завершення");
    ui->LineEditEndMonth->setValidator(month_validator);
    ui->LineEditEndYear->setPlaceholderText("Рік завершення");
    ui->LineEditEndYear->setValidator(year_validator);
}

AddNewAbonement::~AddNewAbonement()
{
    delete ui;
}

void AddNewAbonement::on_LineEditLastName_textChanged()
{
    if(!ui->LineEditLastName->hasAcceptableInput())
    {
        ui->LineEditLastName->setStyleSheet(STYLESHEETERROR);
    }
    else
    {
        ui->LineEditLastName->setStyleSheet(STYLESHEETDEFAULT);
    }
}

void AddNewAbonement::on_LineEditFirstName_textChanged()
{
    if(!ui->LineEditFirstName->hasAcceptableInput())
    {
        ui->LineEditFirstName->setStyleSheet(STYLESHEETERROR);
    }
    else
    {
        ui->LineEditFirstName->setStyleSheet(STYLESHEETDEFAULT);
    }
}

void AddNewAbonement::on_LineEditFathersName_textChanged()
{
    if(!ui->LineEditFathersName->hasAcceptableInput())
    {
        ui->LineEditFathersName->setStyleSheet(STYLESHEETERROR);
    }
    else
    {
        ui->LineEditFathersName->setStyleSheet(STYLESHEETDEFAULT);
    }
}

void AddNewAbonement::on_LineEditDurationPerDay_textChanged()
{
    if(!ui->LineEditDurationPerDay->hasAcceptableInput())
    {
        ui->LineEditDurationPerDay->setStyleSheet(STYLESHEETERROR);
    }
    else
    {
        ui->LineEditDurationPerDay->setStyleSheet(STYLESHEETDEFAULT);
    }
}

void AddNewAbonement::on_LineEditVisitsPerMonth_textChanged()
{
    if(!ui->LineEditVisitsPerMonth->hasAcceptableInput())
    {
        ui->LineEditVisitsPerMonth->setStyleSheet(STYLESHEETERROR);
    }
    else
    {
        ui->LineEditVisitsPerMonth->setStyleSheet(STYLESHEETDEFAULT);
    }
}

void AddNewAbonement::on_LineEditEndDay_textChanged()
{
    if(!ui->LineEditEndDay->hasAcceptableInput())
    {
        ui->LineEditEndDay->setStyleSheet(STYLESHEETERROR);
    }
    else
    {
        ui->LineEditEndDay->setStyleSheet(STYLESHEETDEFAULT);
    }
}

void AddNewAbonement::on_LineEditEndMonth_textChanged()
{
    if(!ui->LineEditEndMonth->hasAcceptableInput())
    {
        ui->LineEditEndMonth->setStyleSheet(STYLESHEETERROR);
    }
    else
    {
        ui->LineEditEndMonth->setStyleSheet(STYLESHEETDEFAULT);
    }
}

void AddNewAbonement::on_LineEditEndYear_textChanged()
{
    if(!ui->LineEditEndYear->hasAcceptableInput())
    {
        ui->LineEditEndYear->setStyleSheet(STYLESHEETERROR);
    }
    else
    {
        ui->LineEditEndYear->setStyleSheet(STYLESHEETDEFAULT);
    }
}

void AddNewAbonement::on_PushButtonAddAbonement_clicked()
{
    bool correctInput=true;
    double duration_per_day;
    int end_day;
    int end_month;
    int end_year;
    int visits_per_month;
    std::string first_name;
    std::string last_name;
    std::string fathers_name;
    do
    {
        if(!ui->LineEditDurationPerDay->hasAcceptableInput())
        {
            ui->LineEditDurationPerDay->setStyleSheet(STYLESHEETERROR);
            correctInput = false;
        }
        else
        {
            ui->LineEditDurationPerDay->setStyleSheet(STYLESHEETDEFAULT);
            duration_per_day = ui->LineEditDurationPerDay->text().toDouble();
        }
        if(!ui->LineEditEndDay->hasAcceptableInput())
        {
            ui->LineEditEndDay->setStyleSheet(STYLESHEETERROR);
            correctInput = false;
        }
        else
        {
            ui->LineEditEndDay->setStyleSheet(STYLESHEETDEFAULT);
            end_day = ui->LineEditEndDay->text().toInt();
        }
        if(!ui->LineEditEndMonth->hasAcceptableInput())
        {
            ui->LineEditEndMonth->setStyleSheet(STYLESHEETERROR);
            correctInput = false;
        }
        else
        {
            ui->LineEditEndMonth->setStyleSheet(STYLESHEETDEFAULT);
            end_month = ui->LineEditEndMonth->text().toInt();
        }
        if(!ui->LineEditEndYear->hasAcceptableInput())
        {
            ui->LineEditEndYear->setStyleSheet(STYLESHEETERROR);
            correctInput = false;
        }
        else
        {
            ui->LineEditEndYear->setStyleSheet(STYLESHEETDEFAULT);
            end_year = ui->LineEditEndYear->text().toInt();
        }
        if(!ui->LineEditFathersName->hasAcceptableInput())
        {
            ui->LineEditFathersName->setStyleSheet(STYLESHEETERROR);
            correctInput = false;
        }
        else
        {
            ui->LineEditFathersName->setStyleSheet(STYLESHEETDEFAULT);
            fathers_name = ui->LineEditFathersName->text().toStdString();
        }
        if(!ui->LineEditFirstName->hasAcceptableInput())
        {
            ui->LineEditFirstName->setStyleSheet(STYLESHEETERROR);
            correctInput = false;
        }
        else
        {
            ui->LineEditFirstName->setStyleSheet(STYLESHEETDEFAULT);
            first_name = ui->LineEditFirstName->text().toStdString();
        }
        if(!ui->LineEditLastName->hasAcceptableInput())
        {
            ui->LineEditLastName->setStyleSheet(STYLESHEETERROR);
            correctInput = false;
        }
        else
        {
            ui->LineEditLastName->setStyleSheet(STYLESHEETDEFAULT);
            last_name = ui->LineEditLastName->text().toStdString();
        }
        if(!ui->LineEditVisitsPerMonth->hasAcceptableInput())
        {
            ui->LineEditVisitsPerMonth->setStyleSheet(STYLESHEETERROR);
            correctInput = false;
        }
        else
        {
            ui->LineEditVisitsPerMonth->setStyleSheet(STYLESHEETDEFAULT);
            visits_per_month = ui->LineEditVisitsPerMonth->text().toInt();
        }
    }while(0);
    if(correctInput)
    {
        bool is_family = ui->RadioButtonIsFamily->isChecked();
        std::set<AdditionalServices> additional_services;
        if(ui->CheckBoxGym->isChecked())
            additional_services.emplace(AdditionalServices::gym);
        if(ui->CheckBoxMassage->isChecked())
            additional_services.emplace(AdditionalServices::massage);
        if(ui->CheckBoxSauna->isChecked())
            additional_services.emplace(AdditionalServices::sauna);
        if(ui->CheckBoxSteamRoom->isChecked())
            additional_services.emplace(AdditionalServices::steam_room);
        if(ui->CheckBoxWaterPark->isChecked())
            additional_services.emplace(AdditionalServices::water_park);
        m_season_ticket = SwimmingPoolSeasonTicket(Person(first_name, last_name, fathers_name)
                                                   ,Date(end_day, end_month, end_year)
                                                   ,duration_per_day,
                                                   static_cast<std::size_t>(visits_per_month),
                                                   is_family,
                                                   additional_services);
        this->close();
    }
}
