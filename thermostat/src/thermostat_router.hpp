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
    ThermostatRouter();

    Response GetResponse(const Request& request);

private:
    Router m_router;
    Thermostat m_thermostat;

    Response Root(Request request);
    Response AddValve(Request request);
    Response SetTarget(Request request);
    Response RemoveValve(Request request);
};
