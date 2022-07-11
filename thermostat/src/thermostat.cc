#include "thermostat.h"


Thermostat::Thermostat()
{
    name_ = "Thermostat";
    desc_ = "DescThermostat.....";
    target_temp_=-1;
    current_temp_=-1;
}

Thermostat::Thermostat(float target_temp)
{
    name_ = "Thermostat";
    desc_ = "DescThermostat.....";
    target_temp_=target_temp;
    current_temp_=-1;
}

float &Thermostat::getTargetTemp()
{
    return target_temp_;
}

void Thermostat::setTargetTemp(float target_temp)
{
    target_temp_=target_temp;
}


float &Thermostat::getCurrentTemp()
{
    return current_temp_;
}

void Thermostat::setCurrentTemp(float sensor_read_temp)
{
    current_temp_=sensor_read_temp;
}