#include "Person.h"
Person::Person()
{

}
Person::Person(const std::string& first_name
       ,const std::string& last_name
       ,const std::string& fathers_name)
{
    if(first_name.empty())
        throw Exception("Invalid first name");
    if(last_name.empty())
        throw Exception("Invalid last name");
    if(fathers_name.empty())
        throw Exception("Invalid fathers name");
    m_first_name = first_name;
    m_last_name = last_name;
    m_fathers_name = fathers_name;
}
Person::Person(const Person& copy)
{
    m_last_name = copy.m_last_name;
    m_first_name = copy.m_first_name;
    m_fathers_name = copy.m_fathers_name;
}
Person::Person(Person&& copy)
{
    m_last_name = std::move(copy.m_last_name);
    m_first_name = std::move(copy.m_first_name);
    m_fathers_name = std::move(copy.m_fathers_name);
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
        throw Exception("Invalid first name");
    m_first_name = first_name;
}
void Person::set_last_name(const std::string& last_name)
{
    if(last_name.empty())
        throw Exception("Invalid last name");
    m_last_name = last_name;
}
void Person::set_fathers_name(const std::string& fathers_name)
{
    if(fathers_name.empty())
        throw Exception("Invalid fathers name");
    m_fathers_name = fathers_name;
}
