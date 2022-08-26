#pragma once

#include <networking/endpoint.hpp>
#include <string>
#include <vector>

class ConfigParser {
public:
    static float GetDefaultTarget();
    static float GetValveTemperatureDifferenceTolerance();
    static std::vector<Endpoint> GetValveAddresses();
    static bool IsValveAlreadyInConfig(const Endpoint& vavlve_address);
    static void AddValveToConfig(const Endpoint& valve_address);
private:
    static float SetDefaultTarget();
    static float SetValveTemperatureDifferenceTolerance();
    static Endpoint SetThermostatEndpoint();
    static std::vector<Endpoint> SetValveAddresses();
    static Endpoint StringToEndpoint(std::string address);

    static float m_default_target;
    static float m_valve_temperature_diff_tolerance;
    static std::vector<Endpoint> m_valve_addresses;
    static std::string m_valve_conf;
    static std::string m_thermostat_conf;
};
