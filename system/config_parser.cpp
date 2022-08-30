#include <iostream>
#include <fstream>
#include "config_parser.hpp"
#include "system.hpp"

std::string ConfigParser::m_path_to_config_files = System::GetConfigPath();
nlohmann::json ConfigParser::m_valve_conf = ConfigParser::GetValveConfigContent();
nlohmann::json ConfigParser::m_thermostat_conf = ConfigParser::GetThermostatConfigContent();

void ConfigParser::InitConfig() {
    m_path_to_config_files = System::GetConfigPath();
    ConfigParser::m_valve_conf = ConfigParser::GetValveConfigContent();
    ConfigParser::m_thermostat_conf = ConfigParser::GetThermostatConfigContent();
}

float ConfigParser::GetDefaultTarget() {
    return m_valve_conf["default_target"].get<uint16_t>();
}

std::vector<Endpoint> ConfigParser::GetValveAddresses() {
    return std::vector<Endpoint>();
}

bool ConfigParser::IsValveAlreadyInConfig(const Endpoint& valve_address) {
    return false;
}

void ConfigParser::AddValveToConfig(const Endpoint& valve_address) {
    
}

nlohmann::json ConfigParser::GetValveConfigContent() {
    if (!System::CommandLineParameters::initialized)
        return nlohmann::json();
    if (!System::FileExists(m_path_to_config_files + "/valve.conf"))
        System::CreateFile(m_path_to_config_files + "/valve.conf", GetDefaultValveConfig().dump());

    std::ifstream fin(m_path_to_config_files + "/valve.conf");
    return nlohmann::json::parse(fin);
}

nlohmann::json ConfigParser::GetThermostatConfigContent() {
    if (!System::CommandLineParameters::initialized)
        return nlohmann::json();
    if (!System::FileExists(m_path_to_config_files + "/thermostat.conf"))
        System::CreateFile(m_path_to_config_files + "/thermostat.conf", GetDefaultThermostatConfig().dump());

    std::ifstream fin(m_path_to_config_files + "/thermostat.conf");
    return nlohmann::json::parse(fin);
}

nlohmann::json ConfigParser::GetDefaultValveConfig() {
    return {
        {"default_target", 18},
        {"temp_diff_tolerance", 0.5}
    };
}

nlohmann::json ConfigParser::GetDefaultThermostatConfig() {
    return {
        "valves_addresses", { }
    };
}
