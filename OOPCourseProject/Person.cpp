#include "Person.h"

Person::Person(const std::string& first_name
       ,const std::string& last_name
       ,const std::string& fathers_name)
{
    if(first_name.empty())
        throw DataException("Invalid first name");
    if(last_name.empty())
        throw DataException("Invalid last name");
    if(fathers_name.empty())
        throw DataException("Invalid fathers name");
    m_first_name = first_name;
    m_last_name = last_name;
    m_fathers_name = fathers_name;
}
std::string Person::get_first_name() const noexcept
{
    return m_first_name;
}
std::string Person::get_last_name() const noexcept
{
    return m_last_name;
}
std::string Person::get_fathers_name() const noexcept
{
    return m_fathers_name;
}
void Person::set_first_name(const std::string& first_name)
{
    if(first_name.empty())
        throw DataException("Invalid first name");
    m_first_name = first_name;
}
void Person::set_last_name(const std::string& last_name)
{
    if(last_name.empty())
        throw DataException("Invalid last name");
    m_last_name = last_name;
}
void Person::set_fathers_name(const std::string& fathers_name)
{
    if(fathers_name.empty())
        throw DataException("Invalid fathers name");
    m_fathers_name = fathers_name;
}
