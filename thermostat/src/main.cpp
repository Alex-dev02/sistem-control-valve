#include <iostream>

#include "../../networking/socket/TcpListener.hpp"
#include "../../networking/router/Router.hpp"
#include "../../networking/socket/NetworkStream.hpp"
#include "Thermostat.hpp"

int main(int argc, char *argv[]) {
    Thermostat t;
    TcpListener server("alex-VirtualBox", "4000");
    server.Start();
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::string req = stream.Read();
        std::cout << req << '\n';
        stream.Write(HTTP::getHTTPResponse(req, t.getRouter()));
        stream.Close();
    }
}