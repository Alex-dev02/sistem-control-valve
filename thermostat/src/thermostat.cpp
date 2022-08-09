#include "thermostat.hpp"

#include <algorithm>
#include <iostream>
#include <networking/tcp_client.hpp>
#include <networking/network_stream.hpp>
#include <networking/iot_dcp.hpp>

bool ValveAddress::operator==(const ValveAddress& valve_addr) {
	return m_server_name == valve_addr.m_server_name & m_port == valve_addr.m_port;
}

Thermostat::Thermostat() {}

void Thermostat::AddValve(const ValveAddress& valve_addr) {
  	m_valves.push_back(valve_addr);
}

bool Thermostat::RemoveValve(const std::string& server_name) {
  	std::vector<ValveAddress>::iterator valve_to_remove = 
		std::find_if(m_valves.begin(), m_valves.end(), [&server_name](const ValveAddress& valves){
			return server_name == valves.m_server_name;
		});
	if (valve_to_remove != m_valves.end()) {
		m_valves.erase(valve_to_remove);
		return true;
	}
	return false;
}

std::vector<Response> Thermostat::WriteToValves(const Request& request) {
	std::vector<Response> responses;
	for (int it = 0; it < m_valves.size(); it++) {
		TcpClient client(m_valves[it].m_port, m_valves[it].m_server_name);
        NetworkStream stream = client.GetStream();
        stream.Write(request.GetRawRequest());
        Response response(stream.Read());
        responses.push_back(response);
        stream.Close();
	}
	return responses;
}

bool Thermostat::PingValve(std::string server_name, std::string port) {
	try {
		TcpClient client(port, server_name);
		NetworkStream stream  = client.GetStream();
		stream.Write(IotDCP().CreateRequest(Utils::RequestType::GET, "/ping").GetRawRequest());
		Response response(stream.Read());
		stream.Close();
	}catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}
	return true;
}
