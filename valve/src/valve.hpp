#pragma once

#include <string>

class Valve {
public:
    Valve();

    float GetCurrentTarget() const;
    float GetTemperature() const;

    void SetCurrentTarget(float current_targer);
    void SetThermostat(std::string ip_address, std::string port);
    void SetValve(std::string ip_address, std::string port);
private:
    float m_current_target;
    float m_temperature;
    std::string m_thermostat_ip_address;
    std::string m_thermostat_port;
    std::string m_ip_address;
    std::string m_port;

    bool PollToThermostat();
    void SetTemperature(float temperature);
    void IncrementTemperature();
    void UpdateValve();
    void DisplayTemperature();
    void UpdateTemperature();
};
