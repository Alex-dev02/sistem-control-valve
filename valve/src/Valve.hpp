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
    void SetCurrentTarget(float current_targer);
private:
    float m_current_target;
    Router m_router;

    std::string SetCurrentTargetRoute(Payload payload);
};
