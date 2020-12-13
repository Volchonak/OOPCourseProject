#ifndef DATE_H
#define DATE_H

#include <string>
#include <sstream>


struct Date{

    Date(const int day, const int month, const int year);
    Date();
    void SetDataFromStr(const std::string& data);
    std::string DataToStr() const noexcept;
    void set_day(const int day);
    void set_month(const int month);
    void set_year( const int year);

    int m_day;
    int m_month;
    int m_year;
};
#endif // DATE_H
