#include "date.hpp"

Date::Date() : m_day(1), m_month(1), m_year(1900), m_hour(0), m_minute(0) {}

Date::Date(int day) : m_day(day), m_month(1), m_year(1900), m_hour(0), m_minute(0) {}

Date::Date(int day, int month) : m_day(day), m_month(month), m_year(1900), m_hour(0), m_minute(0) {}

Date::Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year), m_hour(0), m_minute(0) {}

Date::Date(int day, int month, int year, int hour) : m_day(day), m_month(month), m_year(year), m_hour(hour), m_minute(0) {}

Date::Date(int day, int month, int year, int hour, int minute) : m_day(day), m_month(month), m_year(year), m_hour(hour), m_minute(minute) {}


bool Date::isValid()
{
    return (m_day >= 1 && m_day <=30);
}