#include "Response.hpp"

#include <iostream>
#include <string.h>

Response::Response(std::string raw_response, Utils::Protocol protocol):
    m_raw_response(raw_response),
    m_protocol(protocol)
{}

std::string Response::GetRawResponse() {
    return m_raw_response;
}

Utils::Protocol Response::GetProtocol() {
    return m_protocol;
}

Utils::ResponseCode Response::GetReponseCode() {
    if (m_protocol == Utils::Protocol::IotDCP) {
        return Utils::ResponseCodeToEnum(
            std::stoi(std::string("" + m_raw_response[0]))
        );  
    }
    char* tokens = strtok((char*)(m_raw_response.c_str()), " ");
    if (tokens[1] != NULL)
        return Utils::ResponseCodeToEnum(tokens[1]);
}

bool Response::Successful() {
    return GetReponseCode() == Utils::ResponseCode::OK;
}
