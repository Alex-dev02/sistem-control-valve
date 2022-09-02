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
	bool DisconnectValve(const Endpoint& valve_address);
	std::vector<Response> WriteToValves(const Request& request);
    Response WriteToValve(const Request& request, const Endpoint& valve_address);
	bool ConnectValve(const Endpoint& valve_address);
	void SetAddress(const Endpoint& thermostat_address);
private:
	void UpdateValvesState();
	Endpoint m_address;
    std::unordered_map<std::string, Endpoint> m_valves;
};
