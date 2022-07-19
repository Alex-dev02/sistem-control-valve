#include <iostream>

#include "Valve.hpp"
#include "../../networking/socket/TcpClient.hpp"
#include "../../networking/socket/TcpListener.hpp"
#include "../../networking/socket/NetworkStream.hpp"
#include "../../networking/router/Router.hpp"

int main(int argc, char *argv[]) {
    Valve v;
    TcpListener server(
        argc >= 2 ? argv[1] : "127.0.0.1",
        argc >= 3 ? argv[2] : "5000"
    );
    server.Start();
    Router router = v.GetRouter();
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        std::cout << "Current Temp: " << v.GetTemperature() << '\n';
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::string req = stream.Read();
        std::string res = router.GetPathHandlerResponse(req);
        stream.Write(res);
        stream.Close();
    }
}