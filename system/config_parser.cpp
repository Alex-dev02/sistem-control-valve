#include <iostream>
#include <fstream>
#include "config_parser.hpp"
#include "system.hpp"

std::string ConfigParser::m_path_to_config_files = "";
nlohmann::json ConfigParser::m_valve_conf = ConfigParser::GetValveConfigContent();
nlohmann::json ConfigParser::m_thermostat_conf = ConfigParser::GetThermostatConfigContent();

float ConfigParser::GetDefaultTarget() {
    return 0.5;
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
    std::cout << "Am ajuns aici\n\n\n";
    std::cout << "aaaa" << m_path_to_config_files << "\n\n";
    if (!System::FileExists("/home/valve.conf"))
        System::CreateFile("/home/valve.conf");

    std::ifstream fin("/home/valve.conf");
    return nlohmann::json::parse(fin);
}

nlohmann::json ConfigParser::GetThermostatConfigContent() {
    if (!System::FileExists("/home/thermostat.conf"))
        System::CreateFile("/home/thermostat.conf");

    std::ifstream fin("/home/thermostat.conf");
    return nlohmann::json::parse(fin);
}

