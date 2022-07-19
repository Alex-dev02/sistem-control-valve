#include <iostream>

#include "../../networking/socket/TcpListener.hpp"
#include "../../networking/router/Router.hpp"
#include "../../networking/socket/NetworkStream.hpp"
#include "../../networking/IotDCP/HttpResponses.hpp"
#include "../../networking/IotDCP/Payload.hpp"
#include "Thermostat.hpp"

int main(int argc, char *argv[]) {
    Thermostat t = Thermostat();
    TcpListener server(
        argc >= 2 ? argv[1] : "127.0.0.1",
        argc >= 3 ? argv[2] : "4000"
    );
    server.Start();
    Router router = t.GetRouter();
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::string req = stream.Read();
        std::string res = router.GetPathHandlerResponse(req); 
        if (res == "NULL")
            res = HttpResponses::NotFound();
        else
            res = HttpResponses::OK(res);
        stream.Write(res);
        stream.Close();
    }
}