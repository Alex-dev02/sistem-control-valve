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

int Response::GetReponseCode() {
    if (m_protocol == Utils::Protocol::IotDCP) {
        return Utils::IotDCPResponseCodeToEnum(
            std::stoi(std::string("" + m_raw_response[0]))
        );  
    }

    char* tokens = strtok((char*)(m_raw_response.c_str()), " ");
    try {
        return Utils::HTTPResponseCodeToEnum(tokens[1]);
    }catch(std::string e) {
        return 500;
    }

}

bool Response::Successful() {
    if (m_protocol == Utils::HTTP)
        return
            Utils::HTTPResponseCodeToEnum(GetReponseCode()) == Utils::HTTPResponseCode::H_OK;
    return
        Utils::IotDCPResponseCodeToEnum(GetReponseCode()) == Utils::IotDCPResponseCode::I_OK;
}
