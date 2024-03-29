#include "valve_router.hpp"

#include <iostream>
#include <networking/iot_dcp.hpp>

ValveRouter::ValveRouter(const Endpoint& valve_address):
    m_valve_address(valve_address),
    m_valve(valve_address)
{    
    AddPath("/set_target", std::bind(&ValveRouter::SetCurrentTargetRoute, this, std::placeholders::_1));
    AddPath("/connect", std::bind(&ValveRouter::Connect, this, std::placeholders::_1));
    AddPath("/disconnect", std::bind(&ValveRouter::Disconnect, this, std::placeholders::_1));
    AddPath("/switch_on", std::bind(&ValveRouter::SwitchHeatingOn, this, std::placeholders::_1));
    AddPath("/switch_off", std::bind(&ValveRouter::SwitchHeatingOff, this, std::placeholders::_1));
    AddPath("/is_heating_on", std::bind(&ValveRouter::IsHeatingOn, this, std::placeholders::_1));
    AddPath("/get_temperature", std::bind(&ValveRouter::GetTemperature, this, std::placeholders::_1));
    AddPath("/get_target", std::bind(&ValveRouter::GetTarget, this, std::placeholders::_1));
}

Response ValveRouter::Connect(const Request& request) {
    try
    {
        m_valve.SetThermostat(Endpoint(request.GetIPAddressIotDCP(), request.GetPortIotDCP()));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_ServErr, "Could not extract the PORT from IotDCP request!");
    }
    return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_OK);
}

Response ValveRouter::SetCurrentTargetRoute(const Request& request) {
    IotDCP dcp;
    float target = 0;
    try
    {
        target = std::stof(request.GetPathVar("target"));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return dcp.CreateResponse(Utils::IotDCPResponseCode::I_ServErr);
    }
    
    m_valve.SetCurrentTarget(target);
    return dcp.CreateResponse(Utils::IotDCPResponseCode::I_OK);
}

Response ValveRouter::Disconnect(const Request& request) {
    // checking if the request came from the thermostat that the valve is connected to
    Endpoint thermostat_address;
    try
    {
        thermostat_address = Endpoint(request.GetIPAddressIotDCP(), request.GetPortIotDCP());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_ServErr, "Could not extract the PORT from IotDCP request!");
    }
    if (!(thermostat_address == m_valve.GetThermostatAddress()))
        return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_NotAuth, "Could not disconnect valve!");
    // uninitializing the thermostat
    m_valve.SetThermostat(Endpoint("", 0));
    return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_OK, "Disconnected the valve!");
}

Response ValveRouter::SwitchHeatingOn(const Request& request) {
    m_valve.SwitchOn();
    return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_OK);
}

Response ValveRouter::SwitchHeatingOff(const Request& request) {
    m_valve.SwitchOff();
    return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_OK);
}

Response ValveRouter::IsHeatingOn(const Request& request) {
    return IotDCP().CreateResponse(
        Utils::IotDCPResponseCode::I_OK,
        m_valve.IsOn() ? "1" : "0"
    );
}

Response ValveRouter::GetTemperature(const Request& request){
    return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_OK, std::to_string(m_valve.GetTemperature()));
}

Response ValveRouter::GetTarget(const Request& request){
    return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_OK, std::to_string(m_valve.GetCurrentTarget()));
}
