#include "thermostat_router.hpp"
#include <networking/network_stream.hpp>
#include <networking/iot_dcp.hpp>
#include <networking/http.hpp>

#include <iostream>

ThermostatRouter::ThermostatRouter() {
    // add new paths here
    m_router.AddPath("/", std::bind(&ThermostatRouter::Root, this, std::placeholders::_1));
    m_router.AddPath("/add_valve", std::bind(&ThermostatRouter::AddValve, this, std::placeholders::_1));
    m_router.AddPath("/set_target", std::bind(&ThermostatRouter::SetTarget, this, std::placeholders::_1));
    m_router.AddPath("/remove_valve", std::bind(&ThermostatRouter::RemoveValve, this, std::placeholders::_1));
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
    try
    {
        m_thermostat.AddValve(ValveAddress(
            request.GetPathVar("server_name"),
            request.GetPathVar("port")
        ));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return http.CreateResponse(Utils::HTTPResponseCode::H_ServErr, e.what());
    }
    return http.CreateResponse(Utils::HTTPResponseCode::H_OK, "Valve successfully added!");
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
        "/set_target?target=" + std::to_string(target)
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
    bool succesfully_deleted = true;
    try
    {
        std::string server_name = request.GetPathVar("server_name");
        succesfully_deleted = m_thermostat.RemoveValve(server_name);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return http.CreateResponse(Utils::HTTPResponseCode::H_ServErr, e.what());
    }
    

    return succesfully_deleted ? http.CreateResponse(Utils::HTTPResponseCode::H_OK,"Valve successfully disconnected.")
        : http.CreateResponse(Utils::HTTPResponseCode::H_OK, "Could not find the valve.");
}
