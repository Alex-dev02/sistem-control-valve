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

    auto cool_room = std::thread(&Valve::CoolRoom, this);
    cool_room.detach();
}

float Valve::GetCurrentTarget() const{
    return m_current_target;
}

float Valve::GetTemperature() const{
    return m_temperature;
}

bool Valve::IsOn() {
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

void Valve::SwitchOn() {
    m_heating_on = true;
}

void Valve::SwitchOff() {
    m_heating_on = false;
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

void Valve::IncrementTemperature(float temp_diff_tolernace) {
    if (m_current_target + temp_diff_tolernace - m_temperature > 0)
        m_temperature += 0.1;
}

void Valve::UpdateValve() {
    float temp_diff_tolerance = ConfigParser::GetDefaultTempDiffTolerance();
    while (true) {
        DisplayTemperature();
        if (m_heating_on) {
            UpdateTemperature(temp_diff_tolerance);
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void Valve::DisplayTemperature() {
    std::cout << "Current Target: " << m_current_target << '\n';
    std::cout << "Temperature: " << m_temperature << '\n';
}

void Valve::UpdateTemperature(float temp_diff_tolerance) {
    std::mutex guard;
    std::lock_guard<std::mutex> lock(guard);
    IncrementTemperature(temp_diff_tolerance);
    guard.unlock();
}

void Valve::CoolRoom() {
    std::mutex guard;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(60));
        std::lock_guard<std::mutex> lock(guard);
        m_temperature -= 0.5;
        guard.unlock();
    }
    
}
