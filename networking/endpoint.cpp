#include "endpoint.hpp"

#include <iostream>

Endpoint::Endpoint(std::string ip_address, uint16_t port):
        m_ip_address(ip_address),
        m_port(port)
{
}

Endpoint::Endpoint() {}

std::string Endpoint::GetIPAddress() const{
    return m_ip_address;
}

uint16_t Endpoint::GetPort() const{
    return m_port;
}

bool Endpoint::operator==(const Endpoint& endpoint) const{
	return m_ip_address == endpoint.m_ip_address & m_port == endpoint.m_port;
}