#pragma once

#include <string>

class Valve {
public:
    Valve();

    float GetCurrentTarget();
    float GetTemperature();

    void SetCurrentTarget(float current_targer);
    void SetTemperature(float temperature);
    void IncrementTemperature();

private:
    float m_current_target;
    float m_temperature;
};
