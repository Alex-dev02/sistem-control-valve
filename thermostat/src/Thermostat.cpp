#include "Thermostat.hpp"
#include "../../networking/socket/NetworkStream.hpp"

#include <iostream>

Thermostat::Thermostat() {
    // add new paths here
    m_router.AddPath("/", std::bind(&Thermostat::Root, this, std::placeholders::_1));
    m_router.AddPath("/add_valve", std::bind(&Thermostat::AddValve, this, std::placeholders::_1));
    m_router.AddPath("/set_temperature", std::bind(&Thermostat::SetTemperature, this, std::placeholders::_1));
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
    // int successfuly_updated_valves = 0;
    // for (int it = 0; it < m_valves.size(); it++) {
    //     Socket serv;
    //     int sock_fd = serv.get_sock_fd(m_valves[it].server_name, valves[it].PORT, 10);
    //     std::string res = serv.send_request_to_server(sock_fd, payload.GetRawRequest());
    //     if (res != "NULL" && HTTP::successResponse(res))
    //         successfuly_updated_valves++;
    // }

    // return "Temperature changed to " + payload.GetPathVar("temp")
    //     + " for " + std::to_string(successfuly_updated_valves) + " valves.";
    return "";
}
