#include "valve.hpp"

#include <iostream>

Valve::Valve():
    m_current_target(18),
    m_temperature(18)
{};

float Valve::GetCurrentTarget() const{
    return m_current_target;
}

float Valve::GetTemperature() const{
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
