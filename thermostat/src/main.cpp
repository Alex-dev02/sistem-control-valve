#include <iostream>

#include "../../networking/socket/TcpListener.hpp"
#include "../../networking/router/Router.hpp"
#include "../../networking/socket/NetworkStream.hpp"
#include "../../networking/IotDCP/HttpResponses.hpp"
#include "Thermostat.hpp"

int main(int argc, char *argv[]) {
    Thermostat t;
    TcpListener server("127.0.0.1", "4000");
    server.Start();
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::string req = stream.Read();
        std::cout << req << '\n';
        stream.Write(HttpResponses::ServerError());
        stream.Close();
    }
}