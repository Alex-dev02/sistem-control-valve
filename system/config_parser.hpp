#pragma once

#include <networking/endpoint.hpp>
#include <vector>

class ConfigParser {
public:
    float GetDefaultValveTarget();
    float GetValveTemperatureDifferenceTolerance();
    Endpoint GetThermostatEndpoint();

    //std::vector<Endpoint> GetValveAddresses();
private:
};
