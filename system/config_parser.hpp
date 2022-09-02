#pragma once

#include <networking/endpoint.hpp>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class ConfigParser {
public:
    static void InitConfig();
    static float GetDefaultTarget();
    static float GetDefaultTempDiffTolerance();
    static std::vector<Endpoint> GetValveAddresses();
    static bool IsValveAlreadyInConfig(const Endpoint& valve_address);
    static void AddValveToConfig(const Endpoint& valve_address);
    static std::string m_path_to_config_files;
private:
    static nlohmann::json GetValveConfigContent();
    static nlohmann::json GetThermostatConfigContent();
    static nlohmann::json GetDefaultValveConfig();
    static nlohmann::json GetDefaultThermostatConfig();
    // static float m_default_target;
    // static float m_valve_temperature_diff_tolerance;
    // static std::vector<Endpoint> m_valve_addresses;
    static nlohmann::json m_valve_conf;
    static nlohmann::json m_thermostat_conf;
};
