#include "valve.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

Valve::Valve():
    m_current_target(18),
    m_temperature(18)
{
    auto update_temp_thread = std::thread(&Valve::UpdateValve, this);
    update_temp_thread.detach();
}

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

void Valve::UpdateValve() {
    while (true) {
        DisplayTemperature();
        UpdateTemperature();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void Valve::DisplayTemperature() {
    std::cout << "Current Target: " << m_current_target << '\n';
    std::cout << "Temperature: " << m_temperature << '\n';
}

void Valve::UpdateTemperature() {
    std::mutex guard;
    std::lock_guard<std::mutex> lock(guard);
    IncrementTemperature();
    guard.unlock();
}
