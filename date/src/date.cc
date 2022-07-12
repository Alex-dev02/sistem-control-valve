#include "date.h"

Date::Date() : day_(1), month_(1), year_(1900), hour_(0), minute_(0) {}

Date::Date(int day) : day_(day), month_(1), year_(1900), hour_(0), minute_(0) {}

Date::Date(int day, int month) : day_(day), month_(month), year_(1900), hour_(0), minute_(0) {}

Date::Date(int day, int month, int year) : day_(day), month_(month), year_(year), hour_(0), minute_(0) {}

Date::Date(int day, int month, int year, int hour) : day_(day), month_(month), year_(year), hour_(hour), minute_(0) {}

Date::Date(int day, int month, int year, int hour, int minute) : day_(day), month_(month), year_(year), hour_(hour), minute_(minute) {}


bool Date::isValid()
{
    return (day_ >= 1 && day_ <=30);
}