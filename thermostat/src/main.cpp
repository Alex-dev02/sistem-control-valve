#include <iostream>
#include <system/system.hpp>
#include <networking/server.hpp>
#include <system/system.hpp>
#include <system/config_parser.hpp>

#include "thermostat_router.hpp"

int main(int argc, char *argv[]) {
    System::CommandLineParameters cmd_params = System::GetCmdLineParameters(argc, argv);
    Endpoint thermostat_address;
    try
    {
        thermostat_address = System::GetEndpointToBind(cmd_params); 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
    
    Server<ThermostatRouter> server;
    server.Listen(thermostat_address);
    
    return 0;
}
