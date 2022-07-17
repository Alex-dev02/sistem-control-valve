#include <iostream>

#include "Valve.hpp"
#include "../../networking/socket/TcpClient.hpp"
#include "../../networking/socket/TcpListener.hpp"
#include "../../networking/socket/NetworkStream.hpp"

int main() {
    TcpListener server("127.0.0.1", "5000");
    server.Start();
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::string req = stream.Read();
        std::cout << req << '\n';
        stream.Write("OK");
        stream.Close();
    }
}