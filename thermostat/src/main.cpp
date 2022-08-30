#include <iostream>
#include <system/system.hpp>
#include <networking/server.hpp>
#include <system/system.hpp>
#include <system/config_parser.hpp>
#include "thermostat_router.hpp"

int main(int argc, char *argv[]) {
    System::InitParams(argc, argv);
    Endpoint thermostat_address;
    try
    {
        std::cout << "incercam\n\n";
        ConfigParser::m_path_to_config_files = System::GetConfigPath();
        std::cout << "am si reusit\n\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
            
    try
    {
        thermostat_address = System::GetEndpointToBind(); 
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
