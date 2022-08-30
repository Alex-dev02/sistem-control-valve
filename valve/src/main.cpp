#include <iostream>
#include <networking/server.hpp>
#include <system/system.hpp>
#include <system/config_parser.hpp>

#include "valve_router.hpp"

int main(int argc, char *argv[]) {
    System::InitParams(argc, argv);
    ConfigParser::InitConfig();
    Endpoint valve_address;
    try
    {
        valve_address = System::GetEndpointToBind(); 
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
