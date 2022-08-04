#include "Valve.hpp"

#include <iostream>

Valve::Valve():
    m_current_target(18),
    m_temperature(18)
{
    m_router.AddPath("/set_target", std::bind(&Valve::SetCurrentTargetRoute, this, std::placeholders::_1));
};

Router Valve::GetRouter() {
    return m_router;
}

float Valve::GetCurrentTarget() {
    return m_current_target;
}

float Valve::GetTemperature() {
    return m_temperature;
}

void Valve::SetCurrentTarget(float target) {
    m_current_target = target;
}

void Valve::SetTemperature(float temperature) {
    m_temperature = temperature;
}

void Valve::IncrementTemperature() {
    if (m_current_target - m_temperature >= 0.5)
        m_temperature += 0.5;
    else if (m_current_target - m_temperature <= -0.5)
        m_temperature -= 0.5;
    else if (m_current_target - m_temperature < 0.5)
        m_temperature += (m_current_target - m_temperature);
    else if (m_current_target - m_temperature < 0)
        m_temperature -= (m_current_target - m_temperature);
}

Response Valve::SetCurrentTargetRoute(Request request) {
    IotDCP dcp;
    int target = 0;
    try
    {
        target = std::stof(request.GetPathVar("target"));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return dcp.CreateResponse(Utils::IotDCPResponseCode::I_ServErr);
    }
    
    SetCurrentTarget(target);
    return dcp.CreateResponse(Utils::IotDCPResponseCode::I_OK);
}
