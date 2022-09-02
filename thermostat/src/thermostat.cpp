#include "thermostat.hpp"

#include <algorithm>
#include <iostream>
#include <networking/tcp_client.hpp>
#include <networking/network_stream.hpp>
#include <networking/iot_dcp.hpp>
#include <system/config_parser.hpp>

Thermostat::Thermostat() {}

void Thermostat::AddValve(const Endpoint& valve_address) {
  	m_valves.emplace(
		valve_address.GetIPAddress() + std::to_string(valve_address.GetPort()),
		valve_address
	);
}

bool Thermostat::RemoveValve(const Endpoint& valve_address) {
	auto valve_to_remove = m_valves.find(valve_address.GetIPAddress() + std::to_string(valve_address.GetPort()));
	if (valve_to_remove != m_valves.end()) {
		m_valves.erase(valve_to_remove);
		return true;
	}
	return false;
}

bool Thermostat::DisconnectValve(const Endpoint& valve_address) {
	// checking if the Endpoint of the valve_address isn't the same as thermostat_address

	if (valve_address == m_address)
		return false;


	TcpClient client(valve_address.GetIPAddress(), valve_address.GetPort());
	NetworkStream stream = client.GetStream();
	try
	{
		stream.Write(
			(IotDCP().CreateRequest(
				Utils::RequestType::GET,
				"/disconnect",
				m_address.GetIPAddress(),
				m_address.GetPort()
			).GetRawRequest())
		);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return false;
	}
	return Response(stream.Read()).Successful();
}

std::vector<Response> Thermostat::WriteToValves(const Request& request) {
	std::vector<Response> responses;
	for (auto it = m_valves.begin(); it != m_valves.end(); it++) {
		TcpClient client(it->second.GetIPAddress(), it->second.GetPort());
        NetworkStream stream = client.GetStream();
        try
		{
			stream.Write(request.GetRawRequest());
			Response response(stream.Read());
			responses.push_back(response);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			responses.push_back(IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_ServErr, "Failed to write!"));
		}
        stream.Close();
	}
	return responses;
}

Response Thermostat::WriteToValve(const Request& request, const Endpoint& valve_address) {
	TcpClient client(valve_address.GetIPAddress(), valve_address.GetPort());
	NetworkStream stream = client.GetStream();
	try
	{
		stream.Write(request.GetRawRequest());
		Response response(stream.Read());
		return response;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	stream.Close();
	return IotDCP().CreateResponse(Utils::IotDCPResponseCode::I_ServErr, "Failed to write!");
}

bool Thermostat::ConnectValve(const Endpoint& valve_address) {
	try {
		TcpClient client(valve_address.GetIPAddress(), valve_address.GetPort());
		NetworkStream stream  = client.GetStream();
		stream.Write(
			IotDCP().CreateRequest(Utils::RequestType::GET, "/connect",
			m_address.GetIPAddress(), m_address.GetPort()
        ).GetRawRequest());
		Response response(stream.Read());
		stream.Close();
	}catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}
	return true;
}

void Thermostat::SetAddress(const Endpoint& thermostat_address) {
	m_address = thermostat_address;
}

void Thermostat::UpdateValvesState() {
	float valve_target = 0;
	float valve_temperature = 0;
	float temp_diff_tolerance = ConfigParser::GetDefaultTempDiffTolerance();
	bool heating_on = false;
	for (auto valve = m_valves.begin(); valve != m_valves.end(); valve++) {
		try
		{
			valve_target = std::stof(WriteToValve(
				IotDCP().CreateRequest(Utils::RequestType::GET, "/get_target", m_address.GetIPAddress(), m_address.GetPort()),
				valve->second
			).GetContent());

			valve_temperature = std::stof(WriteToValve(
				IotDCP().CreateRequest(Utils::RequestType::GET, "/get_temperature", m_address.GetIPAddress(), m_address.GetPort()),
				valve->second
			).GetContent());
			heating_on = std::stoi(WriteToValve(
				IotDCP().CreateRequest(Utils::RequestType::GET, "/is_heating_on", m_address.GetIPAddress(), m_address.GetPort()),
				valve->second
			).GetContent());
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

		if (valve_target - valve_temperature >= temp_diff_tolerance && !heating_on) {
			WriteToValve(
				IotDCP().CreateRequest(Utils::RequestType::PUT, "/switch_on", m_address.GetIPAddress(), m_address.GetPort()),
				valve->second
			);
		}

		if (valve_target - valve_temperature <= 0 && heating_on) {
			WriteToValve(
				IotDCP().CreateRequest(Utils::RequestType::PUT, "/switch_off", m_address.GetIPAddress(), m_address.GetPort()),
				valve->second
			);
		}
	}
}
