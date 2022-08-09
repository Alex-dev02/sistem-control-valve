#pragma once

#include <string>
#include <vector>

#include <networking/response.hpp>
#include <networking/request.hpp>

struct ValveAddress {
    std::string m_server_name;
    std::string m_port;
    ValveAddress(std::string server_name, std::string port):
        m_server_name(server_name),
        m_port(port)
    {}
	bool operator==(const ValveAddress& valve_addr);
};

class Thermostat {
public:
	Thermostat();
	
	void AddValve(const ValveAddress& valve_addr);
	bool RemoveValve(const std::string& server_name);
	std::vector<Response> WriteToValves(const Request& request);
    bool PingValve(std::string server_name, std::string port);

private:
	std::vector<ValveAddress> m_valves;
};
