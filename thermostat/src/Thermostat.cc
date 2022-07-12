#include "Thermostat.h"
#include "../../networking/http/HTTP.h"
#include "../../networking/router/Router.h"

#include <iostream>

std::string root(Payload payload) {
    return "Home";
}

std::string Thermostat::add_valve(Payload payload) {
    valves.push_back(Valve_Address(
        payload.get_path_var("server_name"),
        payload.get_path_var("port")
    ));
    return "Valve successfully added!";
}

std::string Thermostat::set_temperature(Payload payload) {

    return "Temperature changed to " + payload.get_path_var("temp");
}

Thermostat::Thermostat(std::string PORT, int BACKLOG)
{
    
    Router router;
    Socket server(PORT, BACKLOG);
    // add new paths here
    router.addPath("/", &root);
    router.addPath("/add_valve", &add_valve);
    router.addPath("/set_temperature", &set_temperature);

    while (true) {
        std::string req = server.accept_new_connection();
        std::cout << '\n' << req << '\n';
        server.respond_to_request(HTTP::getHTTPResponse(req));
    }
}

std::vector<Valve_Address> Thermostat::valves = {};
