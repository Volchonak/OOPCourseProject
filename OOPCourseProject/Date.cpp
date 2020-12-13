#include "Date.h"

Date::Date(const int day, const int month, const int year)
    : m_day(day)
    ,m_month(month)
    ,m_year(year)
{}
Date::Date()
{
    m_day = 0;
    m_month = 0;
    m_year = 0;
}
void Date::SetDataFromStr(const std::string& data)
{
    std::stringstream ss(data);
    std::string token;
    int index = 0;
    while(std::getline(ss, token, '.'))
    {
        switch(index)
        {
        case 0: m_day = std::stoi(token); break;
        case 1: m_month = std::stoi(token); break;
        case 2: m_year = std::stoi(token); break;
        default: break;
        }
        ++index;
    }

}
std::string Date::DataToStr() const noexcept
{
    return std::to_string(m_day) + "."
            + std::to_string(m_month) + "."
            + std::to_string(m_year);
}
void Date::set_day(const int day)
{
    m_day = day;
}
void Date::set_month(const int month)
{
    m_month = month;
}
void Date::set_year( const int year)
{
    m_year = year;
}
