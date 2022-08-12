#include "thermostat.hpp"

#include <algorithm>
#include <iostream>
#include <networking/tcp_client.hpp>
#include <networking/network_stream.hpp>
#include <networking/iot_dcp.hpp>

Thermostat::Thermostat() {}

void Thermostat::AddValve(const Endpoint& valve_address) {
  	m_valves.emplace(
		valve_address.GetIPAddress() + valve_address.GetPort(),
		valve_address
	);
}

bool Thermostat::RemoveValve(const Endpoint& valve_address) {
	auto valve_to_remove = m_valves.find(valve_address.GetIPAddress() + valve_address.GetPort());
	if (valve_to_remove != m_valves.end()) {
		m_valves.erase(valve_to_remove);
		return true;
	}
	return false;
}

std::vector<Response> Thermostat::WriteToValves(const Request& request) {
	std::vector<Response> responses;
	for (auto it = m_valves.begin(); it != m_valves.end(); it++) {
		TcpClient client(it->second.GetIPAddress(), it->second.GetPort());
        NetworkStream stream = client.GetStream();
        stream.Write(request.GetRawRequest());
        Response response(stream.Read());
        responses.push_back(response);
        stream.Close();
	}
	return responses;
}

bool Thermostat::ConnectValve(const Endpoint& valve_address, const Endpoint& thermostat_address) {
	try {
		TcpClient client(valve_address.GetIPAddress(), valve_address.GetPort());
		NetworkStream stream  = client.GetStream();
		stream.Write(
			IotDCP().CreateRequest(Utils::RequestType::GET, "/connect",
			thermostat_address.GetIPAddress(), thermostat_address.GetPort()
        ).GetRawRequest());
		Response response(stream.Read());
		stream.Close();
	}catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}
	return true;
}
