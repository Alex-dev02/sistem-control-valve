#pragma once

#include <string>

class Endpoint {
public:
    Endpoint(std::string ip_address, std::string port);
    Endpoint();
    std::string GetIPAddress() const;
    std::string GetPort() const;
    
    bool operator==(const Endpoint& valve_addr) const;
private:
    std::string m_ip_address;
    std::string m_port;
};
