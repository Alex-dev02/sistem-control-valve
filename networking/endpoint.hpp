#pragma once

#include <string>

class Endpoint {
public:
    Endpoint(std::string ip_address, std::string port);
    std::string GetIPAddress() const;
    std::string GetPort() const;
    
    bool operator==(const Endpoint& valve_addr);
private:
    std::string m_ip_address;
    std::string m_port;
};
