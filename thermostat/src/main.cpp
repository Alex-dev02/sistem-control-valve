#include <iostream>
#include <system/system.hpp>
#include <networking/server.hpp>

#include "thermostat_router.hpp"

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
    uint16_t port = argc >= 2 ? std::stoi(argv[1]) : 4000;
    const Endpoint thermostat_address(ip, port); 
    Server<ThermostatRouter> server;
    server.Listen(thermostat_address);
}
