#include <iostream>
#include <fstream>
#include "config_parser.hpp"
#include "system.hpp"

std::string ConfigParser::m_valve_conf = System::ExecuteCommand("cat ~/valve.conf");
std::string ConfigParser::m_thermostat_conf = System::ExecuteCommand("cat ~/thermostat.conf");

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
