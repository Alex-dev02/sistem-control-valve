#include "thermostat_router.hpp"
#include <networking/network_stream.hpp>
#include <networking/iot_dcp.hpp>
#include <networking/http.hpp>

#include <iostream>

ThermostatRouter::ThermostatRouter(const Endpoint& thermostat_address):
m_thermostat_address(thermostat_address)
{
    // add new paths here
    m_router.AddPath("/", std::bind(&ThermostatRouter::Root, this, std::placeholders::_1));
    m_router.AddPath("/add_valve", std::bind(&ThermostatRouter::AddValve, this, std::placeholders::_1));
    m_router.AddPath("/set_target", std::bind(&ThermostatRouter::SetTarget, this, std::placeholders::_1));
    m_router.AddPath("/remove_valve", std::bind(&ThermostatRouter::RemoveValve, this, std::placeholders::_1));
    m_router.AddPath("/ping", std::bind(&ThermostatRouter::Ping, this, std::placeholders::_1));
}

Response ThermostatRouter::GetResponse(const Request& request) {
    return m_router.GetResponse(request);
}

Response ThermostatRouter::Root(Request request) {
    HTTP http;
    return http.CreateResponse(Utils::HTTPResponseCode::H_OK, "Home");
}

Response ThermostatRouter::AddValve(Request request) {
    HTTP http;
    std::string valve_ip_address;
    std::string valve_port;
    try
    {
        valve_ip_address = request.GetPathVar("server_name");
        valve_port = request.GetPathVar("port");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return http.CreateResponse(Utils::HTTPResponseCode::H_ServErr, "Not enough parameters provided");
    }
    // checking if the valve exists with a ping
    bool connected_successfully = m_thermostat.ConnectValve(
        Endpoint(valve_ip_address, valve_port),
        m_thermostat_address
    );
    if (connected_successfully) {
        m_thermostat.AddValve(Endpoint(valve_ip_address, valve_port));
        return http.CreateResponse(Utils::HTTPResponseCode::H_OK, "Valve successfully added!");
    }
    return http.CreateResponse(Utils::HTTPResponseCode::H_OK, "Could not find the valve!");
}

Response ThermostatRouter::SetTarget(Request request) {
    HTTP http;
    // temperature limit 15 and 28
    float target = 0;
    try
    {
        target = std::stof(request.GetPathVar("target"));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return http.CreateResponse(Utils::HTTPResponseCode::H_ServErr, "The target must be a numeric value.");
    }
    if (target < 15 || target > 28)
        return http.CreateResponse(
            Utils::HTTPResponseCode::H_OK,
            "The temperature can't be lower than 15C or exceed 28C."
        );
    //
    IotDCP dcp;
    int successfuly_updated_valves = 0;
    Request request_to_send = dcp.CreateRequest(
        Utils::RequestType::PUT,
        "/set_target?target=" + std::to_string(target),
        m_thermostat_address.GetIPAddress(),
        m_thermostat_address.GetPort()
    );

    std::vector<Response> responses = m_thermostat.WriteToValves(request_to_send);
    for (int it = 0; it < responses.size(); it++)
        if (responses[it].Successful())
            successfuly_updated_valves++;

    return http.CreateResponse( 
        Utils::HTTPResponseCode::H_OK,
        "Temperature changed to " + std::to_string(target)
        + " for " + std::to_string(successfuly_updated_valves) + " out of "
        + std::to_string(responses.size()) + " valves."
    );
}

Response ThermostatRouter::RemoveValve(Request request) {
    HTTP http;
    bool successfully_deleted = true;
    bool successfully_disconnected = true;
    try
    {
        std::string server_name = request.GetPathVar("server_name");
        std::string port = request.GetPathVar("port");
        successfully_disconnected = m_thermostat.DisconnectValve(
            Endpoint(server_name, port),
            m_thermostat_address
        );
        successfully_deleted = m_thermostat.RemoveValve(Endpoint(server_name, port));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return http.CreateResponse(Utils::HTTPResponseCode::H_ServErr, e.what());
    }
    

    return successfully_deleted || successfully_disconnected ? http.CreateResponse(Utils::HTTPResponseCode::H_OK,"Valve successfully disconnected.")
        : http.CreateResponse(Utils::HTTPResponseCode::H_OK, "Could not find the valve.");
}

Response ThermostatRouter::Ping(Request request) {
    return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_OK);
}
