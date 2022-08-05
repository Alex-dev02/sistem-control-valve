#include "thermostat.hpp"
#include "../../networking/network_stream.hpp"
#include "../../networking/request.hpp"
#include "../../networking/response.hpp"
#include "../../networking/iot_dcp.hpp"
#include "../../networking/http.hpp"

#include <iostream>

Thermostat::Thermostat() {
    // add new paths here
    m_router.AddPath("/", std::bind(&Thermostat::Root, this, std::placeholders::_1));
    m_router.AddPath("/add_valve", std::bind(&Thermostat::AddValve, this, std::placeholders::_1));
    m_router.AddPath("/set_target", std::bind(&Thermostat::SetTarget, this, std::placeholders::_1));
    m_router.AddPath("/remove_valve", std::bind(&Thermostat::RemoveValve, this, std::placeholders::_1));
}

// maybe create a HTTP var inside the Thermostat class ?

Router Thermostat::GetRouter() {
    return m_router;
}

Response Thermostat::Root(Request request) {
    HTTP http;
    // create HTTP response with http class
    return http.CreateResponse(Utils::HTTPResponseCode::H_OK, "Home");
}

Response Thermostat::AddValve(Request request) {
    HTTP http;
    try
    {
        m_valves.push_back(Valve_Address(
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

Response Thermostat::SetTarget(Request request) {
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
        return http.CreateResponse(Utils::HTTPResponseCode::H_ServErr, e.what());
    }
    if (target < 15 || target > 28)
        return http.CreateResponse(
            Utils::HTTPResponseCode::H_OK,
            "The temperature can't be lower than 15C or exceed 28C."
        );
    //
    IotDCP dcp;
    int successfuly_updated_valves = 0;
    for (int it = 0; it < m_valves.size(); it++) {
        TcpClient client(m_valves[it].m_port, m_valves[it].m_server_name);
        NetworkStream stream = client.GetStream();
         Request request = dcp.CreateRequest(
            Utils::RequestType::PUT,
            "/set_target?target=" + std::to_string(target)
        );
        stream.Write(request.GetRawRequest());
        Response response(stream.Read());
        if (response.Successful())
            successfuly_updated_valves++;
        stream.Close();
    }
    return http.CreateResponse( 
        Utils::HTTPResponseCode::H_OK,
        "Temperature changed to " + std::to_string(target)
        + " for " + std::to_string(successfuly_updated_valves) + " out of "
        + std::to_string(m_valves.size()) + " valves."
    );
}

Response Thermostat::RemoveValve(Request request) {
    HTTP http;
    //should receive a "port" variable
    std::string server_name;
    for (std::vector<Valve_Address>::iterator it = m_valves.begin(); it != m_valves.end(); it++) {
        try
        {
            server_name = request.GetPathVar("server_name");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return http.CreateResponse(Utils::HTTPResponseCode::H_ServErr, e.what());
        }
        
        if (it->m_server_name == server_name) {
            m_valves.erase(it);
            return http.CreateResponse(
                Utils::HTTPResponseCode::H_OK,
                "Valve successfully disconnected."
            );
        }
    }
    return http.CreateResponse(
        Utils::HTTPResponseCode::H_OK,
        "Could not find the valve."
    );
}
