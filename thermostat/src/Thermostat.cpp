#include "Thermostat.hpp"
#include "../../networking/tcp/NetworkStream.hpp"
#include "../../networking/IotDCP/Request.hpp"
#include "../../networking/IotDCP/Response.hpp"
#include "../../networking/IotDCP/IotDCP.hpp"

#include <iostream>

Thermostat::Thermostat() {
    // add new paths here
    m_router.AddPath("/", std::bind(&Thermostat::Root, this, std::placeholders::_1));
    m_router.AddPath("/add_valve", std::bind(&Thermostat::AddValve, this, std::placeholders::_1));
    m_router.AddPath("/set_target", std::bind(&Thermostat::SetTarget, this, std::placeholders::_1));
    m_router.AddPath("/remove_valve", std::bind(&Thermostat::RemoveValve, this, std::placeholders::_1));
}

Router Thermostat::GetRouter() {
    return m_router;
}

Response Thermostat::Root(Request request) {
    return Response(Response::HttpOK, "Home");
}

Response Thermostat::AddValve(Request request) {
    m_valves.push_back(Valve_Address(
        request.GetPathVar("server_name"),
        request.GetPathVar("port")
    ));
    return Response(Response::HttpOK, "Valve successfully added!");
}

Response Thermostat::SetTarget(Request request) {
    // temperature limit 15 and 28
    int target = std::stoi(request.GetPathVar("target"));
    if (target < 15 || target > 28)
        return Response(
            Response::HttpOK,
            "The temperature can't be lower than 15C or exceed 28C."
        );
    //
    IotDCP dcp;
    int successfuly_updated_valves = 0;
    for (int it = 0; it < m_valves.size(); it++) {
        TcpClient client(m_valves[it].m_server_name, m_valves[it].m_port);
        NetworkStream stream = client.GetStream();
        std::string req_to_send = dcp.CreateRequest(
            IotDCP::PUT,
            "/set_target?target=" + request.GetPathVar("target")
        );
        stream.Write(req_to_send);
        std::string res = stream.Read();
        if (dcp.IsResponseASuccess(res))
            successfuly_updated_valves++;
        stream.Close();
    }

    return Response( 
        Response::HttpOK,
        "Temperature changed to " + request.GetPathVar("target")
        + " for " + std::to_string(successfuly_updated_valves) + " out of "
        + std::to_string(m_valves.size()) + " valves."
    );
}

Response Thermostat::RemoveValve(Request request) {
    //should receive a "port" variable
    for (std::vector<Valve_Address>::iterator it = m_valves.begin(); it != m_valves.end(); it++) {
        if (it->m_server_name == request.GetPathVar("server_name")) {
            m_valves.erase(it);
            return Response(
                Response::HttpOK,
                "Valve successfully disconnected."
            );
        }
    }
    return Response(
        Response::HttpOK,
        "Coulnd not find the valve."
    );
}
