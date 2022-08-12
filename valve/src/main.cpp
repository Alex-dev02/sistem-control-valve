#include <iostream>

#include <networking/tcp_client.hpp>
#include <networking/tcp_listener.hpp>
#include <networking/network_stream.hpp>
#include <networking/router.hpp>
#include <system/system.hpp>

#include "valve_router.hpp"

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
    std::string port = argc >= 2 ? argv[1] : "5000";
    TcpListener server(port);
    ValveRouter router(ip, port);
    server.Start();
    while (true) {
        std::cout << "Waiting for a new connection...\n";
        TcpClient client = server.AcceptTcpClient();
        NetworkStream stream = client.GetStream();
        std::string req = stream.Read();
        Response res = router.GetResponse(req);
        stream.Write(res.GetRawResponse());
        stream.Close();
    }
}
