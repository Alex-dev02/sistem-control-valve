#include "endpoint.hpp"

#include <iostream>

Endpoint::Endpoint(std::string ip_address, std::string port):
        m_ip_address(m_ip_address),
        m_port(port)
{
    std::cout << m_ip_address << "c" << m_port << "\n";
}

std::string Endpoint::GetIPAddress() const{
    return m_ip_address;
}

std::string Endpoint::GetPort() const{
    return m_port;
}

bool Endpoint::operator==(const Endpoint& endpoint) {
	return m_ip_address == endpoint.m_ip_address & m_port == endpoint.m_port;
}