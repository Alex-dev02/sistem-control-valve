#pragma once

#include <string>

class Valve {
public:
    Valve();

    float GetCurrentTarget() const;
    float GetTemperature() const;

    void SetCurrentTarget(float current_targer);
private:
    float m_current_target;
    float m_temperature;
    std::string m_thermostat_ip_address;
    std::string m_thermostat_port;

    void SetTemperature(float temperature);
    void IncrementTemperature();
    void UpdateValve();
    void DisplayTemperature();
    void UpdateTemperature();
};
