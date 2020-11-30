#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "DataException.h"

class Person
{
public:
    Person();
    Person(const std::string& first_name
           ,const std::string& last_name
           ,const std::string& fathers_name);
    Person(const Person& copy);
    Person(Person&& copy);
    Person& operator= (const Person&) = default;
    std::string get_first_name() const noexcept;
    std::string get_last_name() const noexcept;
    std::string get_fathers_name() const noexcept;
    void set_first_name(const std::string& first_name);
    void set_last_name(const std::string& last_name);
    void set_fathers_name(const std::string& fathers_name);

private:
    std::string m_first_name;
    std::string m_last_name;
    std::string m_fathers_name;
};

#endif // PERSON_H
