#include "SwimmingPoolSeasonTicket.h"


SwimmingPoolSeasonTicket::SwimmingPoolSeasonTicket()
{

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
}
SwimmingPoolSeasonTicket::SwimmingPoolSeasonTicket(const SwimmingPoolSeasonTicket& copy)
{
    m_person = copy.m_person;
    m_end_date = copy.m_end_date;
    m_duration_per_day = copy.m_duration_per_day;
    m_visits_per_month = copy.m_visits_per_month;
    m_is_family = copy.m_is_family;
    m_additional_services = copy.m_additional_services;
}
SwimmingPoolSeasonTicket SwimmingPoolSeasonTicket::operator>>(std::ifstream& file_input)
{
    if(!file_input.is_open())
    {
        //throw exception
    }
    //SwimmingPoolSeasonTicket a;
    //*this = a; redo for smth like this
    return *this;
}
SwimmingPoolSeasonTicket SwimmingPoolSeasonTicket::operator<<(std::ofstream& file_output)
{
    if(!file_output.is_open())
    {
        //throw
    }
    file_output << DataToStr();
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
    data += m_person.get_last_name()
            + m_person.get_first_name()
            + m_person.get_fathers_name();
    data += " " + std::to_string(m_end_date.m_day)
          + "." + std::to_string(m_end_date.m_month)
          + "." + std::to_string(m_end_date.m_year);
    data += " " + std::to_string(m_duration_per_day);
    data += " " + std::to_string(m_visits_per_month);
    data += " " + std::to_string(m_is_family);
    data += " " + AdditionalServicesToStr();

    return data;
}
std::string SwimmingPoolSeasonTicket::AdditionalServicesToStr () const noexcept
{
    std::string data("");
    for(auto i : m_additional_services)
    {
        switch(i)
        {
        case AdditionalServices::sauna: data += " сауна"; break;
        case AdditionalServices::water_park: data += " аквапарк"; break;
        case AdditionalServices::massage: data += " масаж"; break;
        case AdditionalServices::gym: data += " спортзал"; break;
        case AdditionalServices::steam_room: data += " парна"; break;
        }

    }
    data.erase(data.begin());
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
