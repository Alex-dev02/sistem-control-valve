#pragma once

#include "../../networking/router/Router.hpp"
#include "../../networking/IotDCP/Payload.hpp"
#include "../../networking/IotDCP/IotDCP.hpp"

#include <string>

class Valve {
public:
    Valve();

    Router GetRouter();
    float GetCurrentTarget();
    float GetTemperature();

    void SetCurrentTarget(float current_targer);
    void SetTemperature(float temperature);
    void IncrementTemperature();
private:
    float m_current_target;
    float m_temperature;

    Router m_router;

    std::string SetCurrentTargetRoute(Payload payload);
};
