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

std::vector<Endpoint> ConfigParser::GetValveAddresses() {
    return m_valve_addresses;
}

void rec(std::vector<std::string> valve_addreses, std::string str) {
    if (str.length() <= 1)
        return;
    valve_addreses.push_back(str.substr(0, str.find(' ')));
    rec(valve_addreses, str.substr(str.find(' '), str.length()));
}

std::vector<Endpoint> ConfigParser::SetValveAddresses() {
    std::cout << m_thermostat_conf << "\n";
    int addresses_start = m_thermostat_conf.find("valves_addresses:") + std::string("valves_addresses").length() + 1;
    int addresses_stop = addresses_start;
    while (addresses_stop <= m_thermostat_conf.length() &&  m_thermostat_conf[addresses_stop] != '\n'){
        addresses_stop++;
    }
    std::string addresses = m_thermostat_conf.substr(
        m_thermostat_conf[addresses_start] == ' ' ? addresses_start + 1 : addresses_start,
        addresses_stop
    );

    std::vector<std::string> addresses_array;
    std::string address = "";

    for (int it = 0; it < addresses.length(); it++) {
        if (addresses[it] == ' ') {
            addresses_array.push_back(address);
            address = "";
        }
        else
            address += addresses[it];
    }

    addresses_array.push_back(address);
    std::vector<Endpoint> addresses_as_endpoints;

    for (auto it = addresses_array.begin(); it != addresses_array.end(); it++) {
        try
        {
            addresses_as_endpoints.push_back(StringToEndpoint(*it));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return addresses_as_endpoints;
}

Endpoint ConfigParser::StringToEndpoint(std::string address) {
    try
    {
        return Endpoint(
            address.substr(0, address.find(':')),
            std::stoi(address.substr(address.find(':') + 1, address.length()))
        );
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw std::invalid_argument("Bad port!");
    }
}


float ConfigParser::m_default_target = ConfigParser::SetDefaultTarget();
float ConfigParser::m_valve_temperature_diff_tolerance = ConfigParser::SetValveTemperatureDifferenceTolerance();
std::vector<Endpoint> ConfigParser::m_valve_addresses = ConfigParser::SetValveAddresses();