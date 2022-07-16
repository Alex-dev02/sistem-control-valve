#include "Thermostat.hpp"
#include "../../networking/http/HTTP.hpp"
#include "../../networking/socket/NetworkStream.hpp"

#include <iostream>

Thermostat::Thermostat()
{
    // add new paths here
    m_router.addPath("/", std::bind(&Thermostat::root, this, std::placeholders::_1));
    m_router.addPath("/add_valve", std::bind(&Thermostat::add_valve, this, std::placeholders::_1));
    m_router.addPath("/set_temperature", std::bind(&Thermostat::set_temperature, this, std::placeholders::_1));
}

Router Thermostat::getRouter() {
    return m_router;
}

std::string Thermostat::root(Payload payload)
{
    return "Home";
}

std::string Thermostat::add_valve(Payload payload)
{
    valves.push_back(Valve_Address(
        payload.get_path_var("server_name"),
        payload.get_path_var("port")
    ));
    return "Valve successfully added!";
}

std::string Thermostat::set_temperature(Payload payload)
{
    // int successfuly_updated_valves = 0;
    // for (int it = 0; it < valves.size(); it++) {
    //     Socket serv;
    //     int sock_fd = serv.get_sock_fd(valves[it].server_name, valves[it].PORT, 10);
    //     std::string res = serv.send_request_to_server(sock_fd, payload.get_raw_http_req());
    //     if (res != "NULL" && HTTP::successResponse(res))
    //         successfuly_updated_valves++;
    // }

    // return "Temperature changed to " + payload.get_path_var("temp")
    //     + " for " + std::to_string(successfuly_updated_valves) + " valves.";
    return "";
}
