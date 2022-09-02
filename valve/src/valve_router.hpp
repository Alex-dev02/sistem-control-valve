#pragma once

#include "valve.hpp"

#include <networking/router.hpp>
#include <networking/request.hpp>
#include <networking/response.hpp>
#include <networking/endpoint.hpp>

class ValveRouter : public Router{
public:
    ValveRouter(const Endpoint& valve_address);

private:
    Valve m_valve;
    Endpoint m_valve_address;

    Response Connect(const Request& request);
    Response SetCurrentTargetRoute(const Request& request);
    Response Disconnect(const Request& request);
    Response SwitchHeatingOn(const Request& request);
    Response SwitchHeatingOff(const Request& request);
    Response IsHeatingOn(const Request& request);
    Response GetTemperature(const Request& request);
    Response GetTarget(const Request& request);
};
