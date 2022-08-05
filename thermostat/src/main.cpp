#include <iostream>

#include "../../networking/tcp_listener.hpp"
#include "../../networking/router.hpp"
#include "../../networking/network_stream.hpp"
#include "../../networking/response.hpp"
#include "thermostat.hpp"

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