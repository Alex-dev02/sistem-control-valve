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

Thermostat::Thermostat(std::string PORT, int BACKLOG)
{
    Router router;
    // add new paths here
    router.addPath("/", &root);
    router.addPath("/add_valve", &add_valve);

    Socket server(PORT, BACKLOG);
    while (true) {
        std::string req = server.accept_new_connection();
        std::cout << '\n' << req << '\n';
        server.respond_to_request(HTTP::getHTTPResponse(req));
    }
}

std::vector<Valve_Address> Thermostat::valves = {};
