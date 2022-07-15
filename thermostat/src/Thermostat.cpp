#include "Thermostat.hpp"
#include "../../networking/http/HTTP.hpp"
#include "../../networking/router/Router.hpp"

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

Thermostat::Thermostat(std::string PORT, int BACKLOG)
{
    // Router router;
    // Socket server;
    // // add new paths here
    // router.addPath("/", &root);
    // router.addPath("/add_valve", &add_valve);
    // router.addPath("/set_temperature", &set_temperature);
    // int new_fd;
    // int sock = server.get_sock_fd("", PORT, BACKLOG);
    // std::cout << "Waiting for connections...\n";
    // while (true) {
    //     std::string req = server.accept_new_connection(sock, new_fd);
    //     std::cout << '\n' << req << '\n';
    //     server.respond_to_request(HTTP::getHTTPResponse(req), new_fd);
    // }
}

std::vector<Valve_Address> Thermostat::valves = {};
