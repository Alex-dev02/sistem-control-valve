#include <iostream>
#include <networking/tcp_listener.hpp>
#include <networking/router.hpp>
#include <networking/network_stream.hpp>
#include <networking/response.hpp>
#include <networking/endpoint.hpp>
#include <system/system.hpp>

#include "thermostat_router.hpp"

int main(int argc, char *argv[]) {
    std::string ip = "127.0.0.1";
    try
    {
        ip = System::EthPortIP();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::string port = argc >= 2 ? argv[1] : "4000";
    TcpListener server(port);
    const Endpoint thermostat_address(ip, port);
    ThermostatRouter thermostat_router(thermostat_address);
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
