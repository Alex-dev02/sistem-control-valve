#include "iot_dcp.hpp"

IotDCP::IotDCP():
    m_version("0.1")
{}

std::string IotDCP::GetVersion() {
    return m_version;
}

Request IotDCP::CreateRequest(Utils::RequestType type, std::string path, std::string ip_address, std::string port) {
    std::string type_ = type == Utils::GET ? "GET" : "PUT";
    return Request(type_ + ' ' + path + ' ' + "IotDCP/" + m_version + '\n' + ip_address + ' ' + port);
}

Response IotDCP::CreateResponse(Utils::IotDCPResponseCode response_code, std::string content) {
    return Response(
        Utils::ResponseCodeToString(response_code) + ' ' + "IotDCP/" + m_version +
        "\nLength " + std::to_string(content.length()) + '\n' + content
    );
}
