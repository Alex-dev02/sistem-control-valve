#pragma once

#include <networking/request.hpp>
#include <networking/response.hpp>
#include <networking/tcp_listener.hpp>
#include <networking/router.hpp>
#include "thermostat.hpp"

#include <vector>
#include <string>

class ThermostatRouter : public Router{
public:
    ThermostatRouter(const Endpoint& thermostat_address);

private:
    Thermostat m_thermostat;

    Endpoint m_thermostat_address;

    Response Root(const Request& request);
    Response AddValve(const Request& request);
    Response SetTarget(const Request& request);
    Response RemoveValve(const Request& request);
    Response CheckAlive(const Request& request);
};
