#include <iostream>

#include "../../networking/socket/TcpListener.hpp"
#include "../../networking/router/Router.hpp"
#include "../../networking/socket/NetworkStream.hpp"
#include "../../networking/IotDCP/HttpResponses.hpp"
#include "../../networking/IotDCP/Payload.hpp"
#include "Thermostat.hpp"

int main(int argc, char *argv[]) {
    Thermostat t = Thermostat();
    Router router = t.GetRouter();
    HttpResponses http;
    TcpListener server(argc >= 2 ? argv[1] : "4000");
    
    server.Start();
    
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::string req = stream.Read();
        std::string res = router.GetPathHandlerResponse(req); 
        if (res == "NULL")
            res = http.NotFound();
        else
            res = http.OK(res);
        stream.Write(res);
        stream.Close();
    }
}