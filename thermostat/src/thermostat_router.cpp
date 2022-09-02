#include "thermostat_router.hpp"
#include <networking/network_stream.hpp>
#include <networking/iot_dcp.hpp>
#include <networking/http.hpp>
#include <system/config_parser.hpp>

#include <iostream>

ThermostatRouter::ThermostatRouter(const Endpoint& thermostat_address):
m_thermostat_address(thermostat_address)
{
    m_thermostat.SetAddress(thermostat_address);
    std::vector<Endpoint> previous_connected_valves = ConfigParser::GetValveAddresses();

    for (auto it = previous_connected_valves.begin(); it != previous_connected_valves.end(); it++){
        bool connected_successfully = m_thermostat.ConnectValve(*it);
        if (connected_successfully) {
            m_thermostat.AddValve(*it);
        }
    }
    // add new paths here
    AddPath("/", std::bind(&ThermostatRouter::Root, this, std::placeholders::_1));
    AddPath("/add_valve", std::bind(&ThermostatRouter::AddValve, this, std::placeholders::_1));
    AddPath("/set_target", std::bind(&ThermostatRouter::SetTarget, this, std::placeholders::_1));
    AddPath("/remove_valve", std::bind(&ThermostatRouter::RemoveValve, this, std::placeholders::_1));
    AddPath("/check_alive", std::bind(&ThermostatRouter::CheckAlive, this, std::placeholders::_1));
}

Response ThermostatRouter::Root(const Request& request) {
    HTTP http;
    return http.CreateResponse(Utils::HTTPResponseCode::H_OK, "Home");
}

Response ThermostatRouter::AddValve(const Request& request) {
    HTTP http;
    std::string valve_ip_address;
    uint16_t valve_port;
    try
    {
        valve_ip_address = request.GetPathVar("server_name");
        valve_port = std::stoi(request.GetPathVar("port"));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return http.CreateResponse(Utils::HTTPResponseCode::H_ServErr, "Not enough parameters provided");
    }
    Endpoint valve_address(valve_ip_address, valve_port);
    // check if valve is already registred
    if (m_thermostat.IsValveAlreadyRegistred(valve_address))
        return HTTP().CreateResponse(Utils::HTTPResponseCode::H_OK, "Valve already registred");

    // checking if the valve exists with a ping
    bool connected_successfully = m_thermostat.ConnectValve(valve_address);
    if (connected_successfully) {
        if(!ConfigParser::IsValveAlreadyInConfig(valve_address))
            ConfigParser::AddValveToConfig(valve_address);
        m_thermostat.AddValve(valve_address);
        return http.CreateResponse(Utils::HTTPResponseCode::H_OK, "Valve successfully added!");
    }
    return http.CreateResponse(Utils::HTTPResponseCode::H_OK, "Could not find the valve!");
}

Response ThermostatRouter::SetTarget(const Request& request) {
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
    int successfully_updated_valves = 0;
    Request request_to_send = dcp.CreateRequest(
        Utils::RequestType::PUT,
        "/set_target?target=" + std::to_string(target),
        m_thermostat_address.GetIPAddress(),
        m_thermostat_address.GetPort()
    );

    std::vector<Response> responses = m_thermostat.WriteToValves(request_to_send);
    for (int it = 0; it < responses.size(); it++)
        if (responses[it].Successful())
            successfully_updated_valves++;

    return http.CreateResponse( 
        Utils::HTTPResponseCode::H_OK,
        "Temperature changed to " + std::to_string(target)
        + " for " + std::to_string(successfully_updated_valves) + " out of "
        + std::to_string(responses.size()) + " valves."
    );
}

Response ThermostatRouter::RemoveValve(const Request& request) {
    HTTP http;
    bool successfully_deleted = true;
    bool successfully_disconnected = true;
    try
    {
        std::string server_name = request.GetPathVar("server_name");
        uint16_t port = std::stoi(request.GetPathVar("port"));
        successfully_disconnected = m_thermostat.DisconnectValve(Endpoint(server_name, port));
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

Response ThermostatRouter::CheckAlive(const Request& request) {
    return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_OK);
}
