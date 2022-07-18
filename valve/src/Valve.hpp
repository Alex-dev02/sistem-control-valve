#pragma once

#include "../../networking/router/Router.hpp"
#include "../../networking/IotDCP/Payload.hpp"
#include "../../networking/IotDCP/IotDCP.hpp"

#include <string>

class Valve {
public:
    Valve();

    Router GetRouter();
    float GetTemperature();
    void SetTemperature(float temperature);
private:
    float m_temperature;
    Router m_router;

    std::string SetTemperatureRoute(Payload payload);
};
