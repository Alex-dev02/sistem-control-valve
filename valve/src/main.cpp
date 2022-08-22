#include <iostream>
#include <networking/server.hpp>
#include <system/system.hpp>
#include <system/system.hpp>

#include "valve_router.hpp"

int main(int argc, char *argv[]) {
    System::CommandLineParameters cmd_params = System::GetCmdLineParameters(argc, argv);
    const Endpoint valve_address = System::GetEndpointToBind(cmd_params); 
    
    Server<ValveRouter> server;
    server.Listen(valve_address);
}
