#include "IotDCP.hpp"

IotDCP::IotDCP():
    m_version("0.1")
{}

std::string IotDCP::GetVersion() {
    return m_version;
}

Request IotDCP::CreateRequest(IotDCP::RequestType type, std::string path) {
    std::string type_ = type == IotDCP::GET ? "GET" : "PUT";
    return Request(type_ + ' ' + path + ' ' + "IotDCP/" + m_version);
}

Response IotDCP::CreateResponse(IotDCP::ResponseCode response_code, std::string content) {
    return Response(response_code, content); 
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
