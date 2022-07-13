#pragma once
#include "../../component/src/component.h"
#include "../../sensor/src/sensor.h"

class Thermostat : public Component
{
private:
    float target_temp_;
    Sensor sensor_;

public:
    Thermostat();
    Thermostat(float);
   // ~Thermostat();
    float &getCurrentTemp();
    float &getTargetTemp();
    void setTargetTemp(float);
};