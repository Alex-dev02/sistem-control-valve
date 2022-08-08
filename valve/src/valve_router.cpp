#include "valve_router.hpp"

#include <iostream>
#include <networking/iot_dcp.hpp>

ValveRouter::ValveRouter() {
    m_router.AddPath("/set_target", std::bind(&ValveRouter::SetCurrentTargetRoute, this, std::placeholders::_1));
}

Response ValveRouter::GetResponse(const Request& request) {
    return m_router.GetResponse(request);
}

Valve& ValveRouter::GetValve() {
    return m_valve;
}

Response ValveRouter::SetCurrentTargetRoute(Request request) {
    IotDCP dcp;
    float target = 0;
    try
    {
        target = std::stof(request.GetPathVar("target"));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return dcp.CreateResponse(Utils::IotDCPResponseCode::I_ServErr);
    }
    
    m_valve.SetCurrentTarget(target);
    return dcp.CreateResponse(Utils::IotDCPResponseCode::I_OK);
}
