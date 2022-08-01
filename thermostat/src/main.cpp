#include <iostream>

#include "../../networking/tcp/TcpListener.hpp"
#include "../../networking/router/Router.hpp"
#include "../../networking/tcp/NetworkStream.hpp"
#include "../../networking/communication/Response.hpp"
#include "Thermostat.hpp"

int main(int argc, char *argv[]) {
    Thermostat t = Thermostat();
    Router router = t.GetRouter();
    TcpListener server(argc >= 2 ? argv[1] : "4000");
    
    server.Start();
    
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::string req = stream.Read();
        Response res = router.GetResponse(Request(req)); 
        stream.Write(res.GetRawResponse());
        stream.Close();
    }
}