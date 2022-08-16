#pragma once

#include <string>

class Endpoint {
public:
    Endpoint(std::string ip_address, uint16_t port);
    Endpoint();
    std::string GetIPAddress() const;
    uint16_t GetPort() const;
    
    bool operator==(const Endpoint& valve_addr) const;
private:
    std::string m_ip_address;
    uint16_t m_port;
};
