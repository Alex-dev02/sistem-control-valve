#pragma once

#include <networking/endpoint.hpp>
#include <string>
#include <vector>

class ConfigParser {
public:
    static float GetDefaultTarget();
    static float GetValveTemperatureDifferenceTolerance();
    static Endpoint GetThermostatEndpoint();
    static std::vector<std::string> GetValveAddresses();

private:
    static float SetDefaultTarget();
    static float SetValveTemperatureDifferenceTolerance();
    static Endpoint SetThermostatEndpoint();
    static std::vector<std::string> SetValveAddresses();

    static float m_default_target;
    static float m_valve_temperature_diff_tolerance;
    static std::vector<std::string> m_valve_addresses;
    static std::string m_valve_conf;
    static std::string m_thermostat_conf;
};
