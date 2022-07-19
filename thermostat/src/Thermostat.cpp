#include "Thermostat.hpp"
#include "../../networking/socket/NetworkStream.hpp"
#include "../../networking/IotDCP/HttpResponses.hpp"
#include "../../networking/IotDCP/IotDCP.hpp"

#include <iostream>

Thermostat::Thermostat() {
    // add new paths here
    m_router.AddPath("/", std::bind(&Thermostat::Root, this, std::placeholders::_1));
    m_router.AddPath("/add_valve", std::bind(&Thermostat::AddValve, this, std::placeholders::_1));
    m_router.AddPath("/set_target", std::bind(&Thermostat::SetTemperature, this, std::placeholders::_1));
}

Router Thermostat::GetRouter() {
    return m_router;
}

std::string Thermostat::Root(Payload payload) {
    return "Home";
}

std::string Thermostat::AddValve(Payload payload) {
    m_valves.push_back(Valve_Address(
        payload.GetPathVar("server_name"),
        payload.GetPathVar("port")
    ));
    return "Valve successfully added!";
}

std::string Thermostat::SetTemperature(Payload payload) {
    IotDCP dcp;
    int successfuly_updated_valves = 0;
    for (int it = 0; it < m_valves.size(); it++) {
        TcpClient client(m_valves[it].m_server_name, m_valves[it].m_port);
        NetworkStream stream = client.GetStream();
        stream.Write(dcp.CreateRequest(
            "PUT",
            "/set_target?target=" + payload.GetPathVar("target")
            ));
        std::string res = stream.Read();
        if (dcp.IsResponseASuccess(res))
            successfuly_updated_valves++;
        stream.Close();
    }

    return "Temperature changed to " + payload.GetPathVar("target")
        + " for " + std::to_string(successfuly_updated_valves) + " out of "
        + std::to_string(m_valves.size()) + " valves.";
}
