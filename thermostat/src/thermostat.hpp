#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <networking/response.hpp>
#include <networking/request.hpp>
#include <networking/endpoint.hpp>

class Thermostat {
public:
	Thermostat();
	
	void AddValve(const Endpoint& valve_address);
	bool RemoveValve(const Endpoint& valve_address);
	std::vector<Response> WriteToValves(const Request& request);
    bool ConnectValve(const Endpoint& valve_address, const Endpoint& thermostat_address);

private:
    std::unordered_map<std::string, Endpoint> m_valves;
};
