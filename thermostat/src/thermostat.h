#pragma once
#include "../../component/src/component.cc"

class Thermostat : public Component
{
private:
    float target_temp_;
    float current_temp_;

public:
    Thermostat();
    Thermostat(float);
   // ~Thermostat();

    float &getCurrentTemp();
    void setCurrentTemp(float);

    float &getTargetTemp();
    void setTargetTemp(float);
};