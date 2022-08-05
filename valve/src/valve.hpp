#pragma once

#include <networking/router.hpp>
#include <networking/iot_dcp.hpp>
#include <networking/request.hpp>
#include <networking/response.hpp>


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

    Response SetCurrentTargetRoute(Request request);
};
