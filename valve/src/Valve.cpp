#include "Valve.hpp"

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
    if (m_current_target - m_temperature > 0.5)
        m_temperature += 0.5;
    m_temperature += (m_current_target - m_temperature);
}

std::string Valve::SetCurrentTargetRoute(Payload payload) {
    IotDCP dcp;
    SetCurrentTarget(std::stof(payload.GetPathVar("target")));
    return dcp.CreateResponse("1 OK", "");
}
