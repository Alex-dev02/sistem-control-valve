#include <iostream>
#include <networking/tcp_listener.hpp>
#include <networking/router.hpp>
#include <networking/network_stream.hpp>
#include <networking/response.hpp>

#include "thermostat_router.hpp"

int main(int argc, char *argv[]) {
    std::string port = argc >= 2 ? argv[1] : "4000";
    TcpListener server(port);
    ThermostatRouter thermostat_router(server.GetStream().GetIP(), port);
    server.Start();
    
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::string req = stream.Read();
        Response res = thermostat_router.GetResponse(Request(req)); 
        stream.Write(res.GetRawResponse());
        stream.Close();
    }
}
