#include "config_parser.hpp"

float ConfigParser::GetDefaultValveTarget() {
    return 0;    
}

float ConfigParser::GetValveTemperatureDifferenceTolerance() {
    return 0;
}

Endpoint ConfigParser::GetThermostatEndpoint() {
    return Endpoint();
}
