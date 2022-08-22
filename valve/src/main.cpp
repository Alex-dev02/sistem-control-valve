#include <iostream>
#include <networking/server.hpp>
#include <system/system.hpp>
#include <system/system.hpp>

#include "valve_router.hpp"

int main(int argc, char *argv[]) {
    System::CommandLineParameters cmd_params = System::GetCmdLineParameters(argc, argv);
    Endpoint valve_address;
    try
    {
        valve_address = System::GetEndpointToBind(cmd_params); 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
        
    Server<ValveRouter> server;
    server.Listen(valve_address);
    
    return 0;
}
