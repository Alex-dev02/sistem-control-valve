#pragma once
#include "../../component/src/component.hpp"
#include "../../sensor/src/sensor.hpp"

class Thermostat : public Component
{
private:
    float m_target_temp;
    Sensor m_sensor;

public:
    Thermostat();
    Thermostat(float);
   // ~Thermostat();
    float getCurrentTemp();
    float getTargetTemp();
    void setTargetTemp(float);
};