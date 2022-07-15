#include "Thermostat.hpp"
#include "../../networking/http/HTTP.hpp"
#include "../../networking/router/Router.hpp"
#include "../../networking/socket/NetworkStream.hpp"

#include <iostream>

Thermostat::Thermostat(std::string server_name, std::string port)
{
    // Router router;
    // Socket server;
    // // add new paths here
    // router.addPath("/", &root);
    // router.addPath("/add_valve", &add_valve);
    // router.addPath("/set_temperature", &set_temperature);
    TcpListener server(server_name, port);
    server.Start();
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::cout << stream.Read();
    }
}

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

std::vector<Valve_Address> Thermostat::valves = {};
