#include "SwimmingPoolSeasonTicket.h"


SwimmingPoolSeasonTicket::SwimmingPoolSeasonTicket()
{
    m_empty = true;
}
SwimmingPoolSeasonTicket::SwimmingPoolSeasonTicket(const Person& person
                         ,const Date& end_date
                         ,const double duration_per_day
                         ,const std::size_t visits_per_month
                         ,const bool is_family
                         ,const std::set<AdditionalServices>& additional_services)
{
    m_person = person;
    m_end_date = end_date;
    m_duration_per_day = duration_per_day;
    m_visits_per_month = visits_per_month;
    m_is_family = is_family;
    m_additional_services = additional_services;
    m_empty = false;
}
SwimmingPoolSeasonTicket::SwimmingPoolSeasonTicket(const SwimmingPoolSeasonTicket& copy)
{
    m_person = copy.m_person;
    m_end_date = copy.m_end_date;
    m_duration_per_day = copy.m_duration_per_day;
    m_visits_per_month = copy.m_visits_per_month;
    m_is_family = copy.m_is_family;
    m_additional_services = copy.m_additional_services;
    m_empty = copy.m_empty;
}
SwimmingPoolSeasonTicket::SwimmingPoolSeasonTicket(SwimmingPoolSeasonTicket&& copy)
{
    m_person = std::move(copy.m_person);
    m_end_date = std::move(copy.m_end_date);
    m_duration_per_day = copy.m_duration_per_day;
    m_visits_per_month = copy.m_visits_per_month;
    m_is_family = copy.m_is_family;
    m_additional_services = std::move(copy.m_additional_services);
    m_empty = copy.m_empty;
}

SwimmingPoolSeasonTicket& SwimmingPoolSeasonTicket::operator=(const SwimmingPoolSeasonTicket& copy) noexcept
{
    m_person = copy.m_person;
    m_end_date = copy.m_end_date;
    m_duration_per_day = copy.m_duration_per_day;
    m_visits_per_month = copy.m_visits_per_month;
    m_is_family = copy.m_is_family;
    m_additional_services = copy.m_additional_services;
    m_empty = copy.m_empty;
    return *this;
}
SwimmingPoolSeasonTicket& SwimmingPoolSeasonTicket::operator=(SwimmingPoolSeasonTicket&& copy) noexcept
{
    m_person = std::move(copy.m_person);
    m_end_date = std::move(copy.m_end_date);
    m_duration_per_day = copy.m_duration_per_day;
    m_visits_per_month = copy.m_visits_per_month;
    m_is_family = copy.m_is_family;
    m_additional_services = std::move(copy.m_additional_services);
    m_empty = copy.m_empty;
    return *this;
}
Person SwimmingPoolSeasonTicket::get_person() const noexcept
{
    return m_person;
}
std::string SwimmingPoolSeasonTicket::get_first_name() const noexcept
{
    return m_person.get_first_name();
}
std::string SwimmingPoolSeasonTicket::get_last_name() const noexcept
{
    return m_person.get_last_name();
}
std::string SwimmingPoolSeasonTicket::get_fathers_name() const noexcept
{
    return m_person.get_fathers_name();
}
Date SwimmingPoolSeasonTicket::get_end_date() const noexcept
{
    return m_end_date;
}
std::size_t SwimmingPoolSeasonTicket::get_visits_per_month() const noexcept
{
    return m_visits_per_month;
}
std::set<AdditionalServices> SwimmingPoolSeasonTicket::get_additional_services() const noexcept
{
    return m_additional_services;
}
bool SwimmingPoolSeasonTicket::IsFamilyType() const noexcept
{
    return m_is_family;
}
double SwimmingPoolSeasonTicket::get_duration_per_day() const noexcept
{
    return m_duration_per_day;
}
void SwimmingPoolSeasonTicket::set_person(const Person& person)
{
    m_person = person;
}
void SwimmingPoolSeasonTicket::set_first_name(const std::string& first_name)
{
    m_person.set_first_name(first_name);
}
void SwimmingPoolSeasonTicket::set_last_name(const std::string& last_name)
{
    m_person.set_last_name(last_name);
}
void SwimmingPoolSeasonTicket::set_fathers_name(const std::string& fathers_name)
{
    m_person.set_fathers_name(fathers_name);
}
void SwimmingPoolSeasonTicket::set_end_date(const Date& end_date)
{
    m_end_date = end_date;
}
void SwimmingPoolSeasonTicket::set_duration_per_day(const double duration_per_day)
{
    m_duration_per_day = duration_per_day;
}
void SwimmingPoolSeasonTicket::set_visits_per_month(const std::size_t visits_per_month)
{
    m_visits_per_month = visits_per_month;
}
void SwimmingPoolSeasonTicket::set_family_type(const bool is_family)
{
    m_is_family = is_family;
}
void SwimmingPoolSeasonTicket::set_additional_services(const std::set<AdditionalServices>& additional_services)
{
    m_additional_services = additional_services;
}
void SwimmingPoolSeasonTicket::AddAdditionalService(const AdditionalServices additional_service) noexcept
{
    m_additional_services.emplace(additional_service);
}
std::string SwimmingPoolSeasonTicket::DataToStr() const noexcept
{
    std::string data("");
    std::ostringstream duration_per_day;
    duration_per_day << m_duration_per_day;
    data += m_person.get_last_name()
            + "," + m_person.get_first_name()
            + "," + m_person.get_fathers_name();
    data += "," + std::to_string(m_end_date.m_day)
          + "," + std::to_string(m_end_date.m_month)
          + "," + std::to_string(m_end_date.m_year);
    data += "," + duration_per_day.str();
    data += "," + std::to_string(m_visits_per_month);
    data += ",";
    if(m_is_family)
        data += "1";
    else
        data += "0";
    data +=  AdditionalServicesToStr();
    data += "\n";

    return data;
}
std::string SwimmingPoolSeasonTicket::AdditionalServicesToStr () const noexcept
{
    std::string data("");
    for(auto i : m_additional_services)
    {
        switch(i)
        {
        case AdditionalServices::sauna: data += ",сауна"; break;
        case AdditionalServices::water_park: data += ",аквапарк"; break;
        case AdditionalServices::massage: data += ",масаж"; break;
        case AdditionalServices::gym: data += ",спортзал"; break;
        case AdditionalServices::steam_room: data += ",парна"; break;
        }

    }
    return data;
}
void SwimmingPoolSeasonTicket::AddAdditionalService(const std::string& additional_service)
{
    if(additional_service.empty())
    {
        //throw
    }
    if(additional_service == "сауна")
        AddAdditionalService(AdditionalServices::sauna);
    else if(additional_service == "аквапарк")
        AddAdditionalService(AdditionalServices::water_park);
    else if(additional_service == "масаж")
        AddAdditionalService(AdditionalServices::massage);
    else if(additional_service == "спортзал")
        AddAdditionalService(AdditionalServices::gym);
    else if(additional_service == "парна")
        AddAdditionalService(AdditionalServices::steam_room);
    else
        throw std::exception();
    //change exception
}
bool SwimmingPoolSeasonTicket::Empty() const noexcept
{
    return m_empty;
}
void SwimmingPoolSeasonTicket::set_day(const int day)
{
    m_end_date.set_day(day);
}
void SwimmingPoolSeasonTicket::set_month(const int month)
{
    m_end_date.set_month(month);
}
void SwimmingPoolSeasonTicket::set_year( const int year)
{
    m_end_date.set_year(year);
}
std::ifstream& operator>>(std::ifstream& file_input, SwimmingPoolSeasonTicket& season_ticket)
{
    if(!file_input.is_open())
    {
        throw std::runtime_error("File is not opened\n");
    }
    std::string line;
    std::string data;
    std::getline(file_input, line);
    std::stringstream tokens(line);
    int data_index = 0;
    while(std::getline(tokens, data, ','))
    {
        switch(data_index)
        {
        case 0: season_ticket.set_last_name(data); break;
        case 1: season_ticket.set_first_name(data); break;
        case 2: season_ticket.set_fathers_name(data); break;
        case 3: season_ticket.set_day(std::stoi(data)); break;
        case 4: season_ticket.set_month(std::stoi(data)); break;
        case 5: season_ticket.set_year(std::stoi(data)); break;
        case 6:
        {
            std::istringstream string_to_double(data);
            double duration_per_day;
            string_to_double >> duration_per_day;
            season_ticket.set_duration_per_day(duration_per_day); break;
        }
        case 7: season_ticket.set_visits_per_month(static_cast<std::size_t>(std::stoi(data))); break;
        case 8: season_ticket.set_family_type(std::stoi(data)); break;
        default: season_ticket.AddAdditionalService(data);
        }
        ++data_index;
    }
    if(data_index < 8)
        throw std::runtime_error("Invalid data\n");
    return file_input;
}
std::ofstream& operator<<(std::ofstream& file_output, SwimmingPoolSeasonTicket& season_ticket)
{
    if(!file_output.is_open())
    {
        throw std::runtime_error("File is not opened\n");
    }
    file_output << season_ticket.DataToStr();
    return file_output;
}












