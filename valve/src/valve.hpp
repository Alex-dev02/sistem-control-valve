#pragma once

#include "../../networking/router/router.hpp"
#include "../../networking/communication/iot_dcp.hpp"
#include "../../networking/communication/request.hpp"
#include "../../networking/communication/response.hpp"


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
