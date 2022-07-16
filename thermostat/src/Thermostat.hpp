#pragma once

#include "../../networking/socket/TcpListener.hpp"
#include "../../networking/IotDCP/Payload.hpp"
#include "../../networking/router/Router.hpp"

#include <vector>
#include <string>

 struct Valve_Address {
    std::string m_server_name;
    std::string m_port;
    Valve_Address(std::string server_name, std::string port):
        m_server_name(server_name),
        m_port(port)
    {}
 };

class Thermostat
{
public:
    Thermostat();
    Router GetRouter();
private:
    Router m_router;
    std::vector<Valve_Address> m_valves;

    std::string Root(Payload payload);
    std::string AddValve(Payload payload);
    std::string SetTemperature(Payload payload);
};
