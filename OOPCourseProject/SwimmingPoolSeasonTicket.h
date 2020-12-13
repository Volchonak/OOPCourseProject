#ifndef SWIMMINGPOOLSEASONTICKET_H
#define SWIMMINGPOOLSEASONTICKET_H


#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "Person.h"
#include "Exception.h"
#include "Date.h"

enum class AdditionalServices
{
    sauna
    ,water_park
    ,massage
    ,gym
    ,steam_room
};

class SwimmingPoolSeasonTicket
{
public:
    SwimmingPoolSeasonTicket();
    SwimmingPoolSeasonTicket(const Person& person
                             ,const Date& end_data
                             ,const double duration_per_day
                             ,const std::size_t visits_per_month
                             ,const bool is_family
                             ,const std::set<AdditionalServices>& additional_services);
    SwimmingPoolSeasonTicket(const SwimmingPoolSeasonTicket& copy);
    SwimmingPoolSeasonTicket(SwimmingPoolSeasonTicket&& copy);
    bool IsFamilyType() const noexcept;
    Person get_person() const noexcept;
    std::string get_first_name() const noexcept;
    std::string get_last_name() const noexcept;
    std::string get_fathers_name() const noexcept;
    Date get_end_date() const noexcept;
    std::size_t get_visits_per_month() const noexcept;
    std::set<AdditionalServices> get_additional_services() const noexcept;
    SwimmingPoolSeasonTicket& operator=(const SwimmingPoolSeasonTicket& copy) noexcept;
    SwimmingPoolSeasonTicket& operator=(SwimmingPoolSeasonTicket&& copy) noexcept;
    double get_duration_per_day() const noexcept;
    void set_person(const Person& person);
    void set_first_name(const std::string& first_name);
    void set_last_name(const std::string& last_name);
    void set_fathers_name(const std::string& fathers_name);
    void set_end_date(const Date& end_date);
    void set_day(const int day);
    void set_month(const int month);
    void set_year( const int year);
    void set_duration_per_day(const double duration_per_day);
    void set_visits_per_month(const std::size_t visits_per_month);
    void set_family_type(const bool is_family);
    void set_additional_services(const std::set<AdditionalServices>& additional_services);
    void AddAdditionalService(const AdditionalServices additional_service) noexcept;
    void AddAdditionalService(const std::string& additional_service);
    bool Empty() const noexcept;

    friend std::ifstream& operator>>(std::ifstream& file_input, SwimmingPoolSeasonTicket& season_ticket);
    friend std::ofstream& operator<<(std::ofstream& file_output, SwimmingPoolSeasonTicket& season_ticket);


private:
    std::string DataToStr() const noexcept;
    std::string AdditionalServicesToStr () const noexcept;

    Person m_person;
    Date m_end_date;
    double m_duration_per_day;
    std::size_t m_visits_per_month;
    bool m_is_family;
    bool m_empty;
    std::set<AdditionalServices> m_additional_services;
};

#endif // SWIMMINGPOOLSEASONTICKET_H
