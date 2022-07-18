#include "IotDCP.hpp"

IotDCP::IotDCP(std::string version):
    m_version(version)
{}

std::string IotDCP::GetVersion() {
    return m_version;
}

std::string IotDCP::CreateRequest(std::string type, std::string path) {
    return type + ' ' + path + ' ' + "IotDCP/" + m_version;
}

std::string IotDCP::CreateResponse(std::string response_code, std::string content) {
    return response_code + ' ' + "IotDCP/" + m_version + '\n' +
        "Length " + std::to_string(content.length()) +
        (content.length() == 0 ? "" : '\n' + content); 
}

bool IotDCP::IsResponseASuccess(std::string response) {
    if (response[0] == '1')
        return true;
    return false;
}
