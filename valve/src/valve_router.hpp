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

    Response Connect(Request request);
    Response SetCurrentTargetRoute(Request request);
    Response Disconnect(Request request);
    Response SwitchHeatingOn(Request request);
    Response SwithHeatingOff(Request request);
    Response GetTemperature(Request request);
    Response GetTarget(Request request);
};
