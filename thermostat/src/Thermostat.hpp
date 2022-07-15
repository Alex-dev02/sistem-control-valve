#pragma once

#include "../../networking/socket/TcpListener.hpp"
#include "../../networking/http/Payload.hpp"

#include <vector>
#include <string>

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
public:

    Thermostat(std::string server_name = "", std::string port = "4000");

private:
    static std::vector<Valve_Address> valves;
    static std::string add_valve(Payload payload);
    static std::string set_temperature(Payload payload);
};
