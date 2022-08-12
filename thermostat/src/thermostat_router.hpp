#pragma once

#include <networking/request.hpp>
#include <networking/response.hpp>
#include <networking/tcp_listener.hpp>
#include <networking/router.hpp>
#include "thermostat.hpp"

#include <vector>
#include <string>

class ThermostatRouter {
public:
    ThermostatRouter(std::string ip_address, std::string port = "4000");

    Response GetResponse(const Request& request);

private:
    Router m_router;
    Thermostat m_thermostat;

    std::string m_port;
    std::string m_ip_address;

    Response Root(Request request);
    Response AddValve(Request request);
    Response SetTarget(Request request);
    Response RemoveValve(Request request);
    Response Ping(Request request);
};
