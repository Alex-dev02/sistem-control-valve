#include "Valve.hpp"

Valve::Valve():
    m_current_target(18)
{
    m_router.AddPath("/set_temperature", std::bind(&Valve::SetCurrentTargetRoute, this, std::placeholders::_1));
};

Router Valve::GetRouter() {
    return m_router;
}

float Valve::GetCurrentTarget() {
    return m_current_target;
}

void Valve::SetCurrentTarget(float target) {
    m_current_target = target;
}

std::string Valve::SetCurrentTargetRoute(Payload payload) {
    IotDCP dcp;
    SetCurrentTarget(std::stof(payload.GetPathVar("temp")));
    return dcp.CreateResponse("1 OK", "");
}
