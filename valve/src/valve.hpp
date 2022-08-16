#pragma once

#include <string>
#include <networking/endpoint.hpp>

class Valve {
public:
    Valve(const Endpoint& valve_address);

    float GetCurrentTarget() const;
    float GetTemperature() const;
    const Endpoint& GetThermostatAddress() const;

    void SetCurrentTarget(float current_targer);
    void SetThermostat(const Endpoint& thermostat_address);
private:
    float m_current_target;
    float m_temperature;
    Endpoint m_thermostat_address;
    Endpoint m_valve_address;

    bool PollToThermostat();
    void SetTemperature(float temperature);
    void IncrementTemperature();
    void UpdateValve();
    void DisplayTemperature();
    void UpdateTemperature();
};
