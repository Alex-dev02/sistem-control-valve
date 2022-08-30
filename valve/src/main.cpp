#include <iostream>
#include <networking/server.hpp>
#include <system/system.hpp>
#include <system/system.hpp>

#include "valve_router.hpp"

int main(int argc, char *argv[]) {
    System::InitParams(argc, argv);
    Endpoint valve_address;
    std::cout << "\n" << valve_address.GetIPAddress() << " " << valve_address.GetPort() << "\n";
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
