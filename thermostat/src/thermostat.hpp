#pragma once

#include <networking/request.hpp>
#include <networking/response.hpp>
#include <networking/tcp_listener.hpp>
#include <networking/router.hpp>

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

class Thermostat {
public:
    Thermostat();
    Router GetRouter();
private:
    Router m_router;
    std::vector<Valve_Address> m_valves;

    Response Root(Request request);
    Response AddValve(Request request);
    Response SetTarget(Request request);
    Response RemoveValve(Request request);
};
