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
    // prepare the http req
    std::string http_req;
    for (int it = 0; it < valves.size(); it++) {
        Socket serv;
        int sock_fd = serv.get_sock_fd(valves[it].server_name, valves[it].PORT, 10);
        serv.send_request_to_server(sock_fd, payload.get_raw_http_req());
    }

    return "Temperature changed to " + payload.get_path_var("temp");
}

Thermostat::Thermostat(std::string PORT, int BACKLOG)
{
    Router router;
    Socket server;
    // add new paths here
    router.addPath("/", &root);
    router.addPath("/add_valve", &add_valve);
    router.addPath("/set_temperature", &set_temperature);
    int new_fd;
    int sock = server.get_sock_fd("", PORT, BACKLOG);
    std::cout << "Waiting for connections...\n";
    while (true) {
        std::string req = server.accept_new_connection(sock, new_fd);
        std::cout << '\n' << req << '\n';
        server.respond_to_request(HTTP::getHTTPResponse(req), new_fd);
    }
}

std::vector<Valve_Address> Thermostat::valves = {};
