#include "thermostat.h"

Thermostat::Thermostat()
{
    name_ = "Thermostat";
    desc_ = "DescThermostat.....";
}
Thermostat::Thermostat(float target_temp)
{
    name_ = "Thermostat";
    desc_ = "DescThermostat.....";
    target_temp_ = target_temp;
}

float &Thermostat::getTargetTemp()
{
    return target_temp_;
}

void Thermostat::setTargetTemp(float target_temp)
{
    target_temp_ = target_temp;
}

float &Thermostat::getCurrentTemp()
{

    return sensor_.getTemp();
}
