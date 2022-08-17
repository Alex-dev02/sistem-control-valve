#include <iostream>
#include <networking/server.hpp>
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
    uint16_t port = argc >= 2 ? std::stoi(argv[1]) : 5000;
    const Endpoint valve_address(ip, port);
    Server<ValveRouter> server;
    server.Listen(valve_address);
}
