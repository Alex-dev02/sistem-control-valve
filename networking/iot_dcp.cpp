#include "iot_dcp.hpp"

IotDCP::IotDCP():
    m_version("0.1")
{}

std::string IotDCP::GetVersion() const{
    return m_version;
}

Request IotDCP::CreateRequest(Utils::RequestType type, std::string path, std::string ip_address, uint16_t port) const{
    std::string type_ = type == Utils::GET ? "GET" : "PUT";
    return Request(type_ + ' ' + path + ' ' + "IotDCP/" + m_version + '\n' + ip_address + ' ' + std::to_string(port));
}

Response IotDCP::CreateResponse(Utils::IotDCPResponseCode response_code, std::string content) const{
    return Response(
        Utils::ResponseCodeToString(response_code) + ' ' + "IotDCP/" + m_version +
        "\nLength " + std::to_string(content.length()) + '\n' + content
    );
}
