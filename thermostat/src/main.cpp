#include <iostream>
#include <system/system.hpp>
#include <networking/server.hpp>
#include <system/system.hpp>

#include "thermostat_router.hpp"

int main(int argc, char *argv[]) {
    System::CommandLineParameters cmd_params = System::GetCmdLineParameters(argc, argv);
    const Endpoint thermostat_address = System::GetEndpointToBind(cmd_params); 

    Server<ThermostatRouter> server;
    server.Listen(thermostat_address);
}
