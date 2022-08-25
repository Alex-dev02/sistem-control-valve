#include <iostream>
#include "config_parser.hpp"
#include "system.hpp"

std::string ConfigParser::m_valve_conf = System::ExecuteCommand("cat /usr/local/bin/valve.conf");
std::string ConfigParser::m_thermostat_conf = System::ExecuteCommand("cat /usr/local/bin/thermostat.conf");


float ConfigParser::GetDefaultTarget() {
    return m_default_target;
}

float ConfigParser::GetValveTemperatureDifferenceTolerance() {
    return m_valve_temperature_diff_tolerance;
}

float ConfigParser::SetDefaultTarget() {
    int default_target_pos = m_valve_conf.find("default_target:");
    if (default_target_pos == std::string::npos)
        throw std::runtime_error("No default_target found in valve.conf!");

    default_target_pos += std::string("default_target:").length();
    std::string default_target = "";

    while (m_valve_conf[default_target_pos] != '\n') {
        default_target += m_valve_conf[default_target_pos];
        default_target_pos++;
    }

    try
    {
        return std::stof(default_target);
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error("Invalid default_target in valve.conf!");
    }
}

float ConfigParser::SetValveTemperatureDifferenceTolerance() {
    int temp_diff_tolerance_pos = m_valve_conf.find("temp_diff_tolerance:");
    if (temp_diff_tolerance_pos == std::string::npos)
        throw std::runtime_error("No temp_diff_tolerance found in valve.conf!");

    temp_diff_tolerance_pos += std::string("temp_diff_tolerance:").length();
    std::string temp_diff_tolerance = "";

    while (m_valve_conf[temp_diff_tolerance_pos] != '\n') {
        temp_diff_tolerance += m_valve_conf[temp_diff_tolerance_pos];
        temp_diff_tolerance_pos++;
    }
    try
    {
        return std::stof(temp_diff_tolerance);
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error("Invalid temp_diff_tolerance in valve.conf!");
    }
}

Endpoint ConfigParser::SetThermostatEndpoint() {
    return Endpoint();
}

std::vector<std::string> ConfigParser::GetValveAddresses() {
    return m_valve_addresses;
}

void rec(std::vector<std::string> valve_addreses, std::string str) {
    if (str.length() <= 1)
        return;
    valve_addreses.push_back(str.substr(0, str.find(' ')));
    rec(valve_addreses, str.substr(str.find(' '), str.length()));
}

std::vector<std::string> ConfigParser::SetValveAddresses() {
    std::cout << m_thermostat_conf << "\n";
    int valve_addresses_pos = m_thermostat_conf.find("valve_addresses:") + std::string("valve_addresses").length() + 1;
    int stop = 0, it = valve_addresses_pos;
    while (m_thermostat_conf[it] != '\n')
        it++;
    stop = it;
    std::cout << "it " << m_thermostat_conf[it] << " it\n"; 
    std::string str = m_thermostat_conf.substr(
        valve_addresses_pos, stop
    );
    std::vector<std::string> vec;
    std::cout << "aici\n";
    rec(vec, str);
    std::cout << "aici nu \n";
    return vec;

}

float ConfigParser::m_default_target = ConfigParser::SetDefaultTarget();
float ConfigParser::m_valve_temperature_diff_tolerance = ConfigParser::SetValveTemperatureDifferenceTolerance();
std::vector<std::string> ConfigParser::m_valve_addresses = ConfigParser::SetValveAddresses();