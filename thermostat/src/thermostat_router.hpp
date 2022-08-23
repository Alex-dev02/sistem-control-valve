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

    Response Root(Request request);
    Response AddValve(Request request);
    Response SetTarget(Request request);
    Response RemoveValve(Request request);
    Response CheckAlive(Request request);
};
