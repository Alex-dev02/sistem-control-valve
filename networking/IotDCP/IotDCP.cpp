#include "IotDCP.hpp"

IotDCP::IotDCP():
    m_version("0.1")
{}

std::string IotDCP::GetVersion() {
    return m_version;
}

std::string IotDCP::CreateRequest(IotDCP::RequestType type, std::string path) {
    return 
        type == IotDCP::GET ? "GET" : "PUT"
        + ' ' + path + ' ' + "IotDCP/" + m_version;
}

std::string IotDCP::CreateResponse(IotDCP::ResponseCode response_code, std::string content) {
    return ResponseCodeToString(response_code) + ' ' + "IotDCP/" + m_version + '\n' +
        "Length " + std::to_string(content.length()) +
        (content.length() == 0 ? "" : '\n' + content); 
}

bool IotDCP::IsResponseASuccess(std::string response) {
    if (response[0] == '1')
        return true;
    return false;
}

std::string IotDCP::ResponseCodeToString(IotDCP::ResponseCode response_code) {
    switch (response_code) {
        case IotDCP::ResponseCode::ServErr : return  "0 Server Error";
        case IotDCP::ResponseCode::OK : return "1 OK";
        case IotDCP::ResponseCode::NotFound : "2 Not Found";
        case IotDCP::ResponseCode::NotAuth : "3 Not Authorized";
    }
    return "0 Server Error";
}
