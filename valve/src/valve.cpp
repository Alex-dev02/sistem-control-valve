#include "valve.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <networking/tcp_client.hpp>
#include <networking/iot_dcp.hpp>
#include <system/config_parser.hpp>

Valve::Valve(const Endpoint& valve_address):
    m_current_target(ConfigParser::GetDefaultTarget()),
    m_temperature(ConfigParser::GetDefaultTarget()),
    m_valve_address(valve_address),
    m_heating_on(false)
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

bool Valve::On() {
    return m_heating_on;
}

const Endpoint& Valve::GetThermostatAddress() const {
    return m_thermostat_address;
}

void Valve::SetCurrentTarget(float target) {
    m_current_target = target;
}

void Valve::SetThermostat(const Endpoint& thermostat_address) {
    m_thermostat_address = thermostat_address;
}

bool Valve::PollToThermostat() {
    // check if endpoint is init
    if (m_thermostat_address.GetIPAddress().empty())
        return false;
    try
    {
        TcpClient client(m_thermostat_address.GetIPAddress(), m_thermostat_address.GetPort());
        NetworkStream stream = client.GetStream();
        stream.Write(IotDCP().CreateRequest(
            Utils::RequestType::GET,
            "/check_alive",
            m_valve_address.GetIPAddress(),
            m_valve_address.GetPort()
        ).GetRawRequest());
        Response response = stream.Read();
        return response.Successful();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
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
