#pragma once

#include "../../networking/socket/TcpListener.hpp"
#include "../../networking/http/Payload.h"

#include <vector>

 struct Valve_Address {
    std::string server_name;
    std::string PORT;
    Valve_Address(std::string server_name, std::string PORT):
        server_name(server_name),
        PORT(PORT)
    {}
 };

class Thermostat
{
    static std::vector<Valve_Address> valves;
    static std::string add_valve(Payload payload);
    static std::string set_temperature(Payload payload);
public:
    Thermostat(std::string PORT, int BACKLOG);
};
