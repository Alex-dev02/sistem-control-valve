#include "Valve.hpp"

Valve::Valve():
    m_temperature(18)
{
    m_router.AddPath("/set_temperature", std::bind(&Valve::SetTemperatureRoute, this, std::placeholders::_1));
};

Router Valve::GetRouter() {
    return m_router;
}

float Valve::GetTemperature() {
    return m_temperature;
}

void Valve::SetTemperature(float temperature) {   m_temperature = temperature;
}

std::string Valve::SetTemperatureRoute(Payload payload) {
    IotDCP dcp;
    SetTemperature(std::stof(payload.GetPathVar("temp")));
    return dcp.CreateResponse("1 OK", "");
}
