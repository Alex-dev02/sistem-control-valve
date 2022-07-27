#include "IotDCP.hpp"

IotDCP::IotDCP():
    m_version("0.1")
{}

std::string IotDCP::GetVersion() {
    return m_version;
}

Request IotDCP::CreateRequest(Utils::RequestType type, std::string path) {
    std::string type_ = type == Utils::GET ? "GET" : "PUT";
    return Request(type_ + ' ' + path + ' ' + "IotDCP/" + m_version);
}

Response IotDCP::CreateResponse(Utils::ResponseCode response_code, std::string content) {
    return Response(
        ResponseCodeToString(response_code) + ' ' + "IotDCP/" + m_version +
        "\nLength " + std::to_string(content.length()) + '\n' + content,
        Utils::IotDCP
    );
}
