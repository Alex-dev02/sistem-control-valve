#pragma once

#include "../../networking/socket/TcpListener.hpp"
#include "../../networking/http/Payload.hpp"
#include "../../networking/router/Router.hpp"

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
    Thermostat();
    Router getRouter();
private:
    Router m_router;

    std::vector<Valve_Address> valves;
    std::string root(Payload payload);
    std::string add_valve(Payload payload);
    std::string set_temperature(Payload payload);
};
