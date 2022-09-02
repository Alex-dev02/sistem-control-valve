#pragma once

#include <string>
#include <networking/endpoint.hpp>

class Valve {
public:
    Valve(const Endpoint& valve_address);

    float GetCurrentTarget() const;
    float GetTemperature() const;
    bool IsOn();
    const Endpoint& GetThermostatAddress() const;

    void SetCurrentTarget(float current_targer);
    void SetThermostat(const Endpoint& thermostat_address);
    void SwitchOn();
    void SwitchOff();
private:
    bool m_heating_on;
    float m_current_target;
    float m_temperature;
    Endpoint m_thermostat_address;
    Endpoint m_valve_address;

    bool PollToThermostat();
    void SetTemperature(float temperature);
    void IncrementTemperature(float temp_diff_tolerance);
    void UpdateValve();
    void DisplayTemperature();
    void UpdateTemperature(float temp_diff_tolerance);
    void CoolRoom();
};
