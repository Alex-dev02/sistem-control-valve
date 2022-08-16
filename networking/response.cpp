#include "response.hpp"

#include <iostream>
#include <string.h>

Response::Response(std::string raw_response):
    m_raw_response(raw_response)
{
    if(raw_response.find("IotDCP") != std::string::npos)
        m_protocol = Utils::Protocol::IotDCP;
    else if (raw_response.find("HTTP") != std::string::npos)
        m_protocol = Utils::Protocol::HTTP;
    // else invalid response
    // try to handle
}

std::string Response::GetRawResponse() const{
    return m_raw_response;
}

Utils::Protocol Response::GetProtocol() const{
    return m_protocol;
}

int Response::GetReponseCode() const{
    if (m_protocol == Utils::Protocol::IotDCP) {
        return Utils::IotDCPResponseCodeToEnum(
            m_raw_response[0] - '0'
        );  
    }
    try {
        std::string raw_response_copy = m_raw_response;
        raw_response_copy.erase(0, raw_response_copy.find(' ') + 1);
        return std::stoi(raw_response_copy.substr(0, raw_response_copy.find(' ')));
    }catch(std::string e) {
        return 500;
    }

}

bool Response::Successful() const{
    if (m_protocol == Utils::HTTP)
        return
            Utils::HTTPResponseCodeToEnum(GetReponseCode()) == Utils::HTTPResponseCode::H_OK;
    return
        Utils::IotDCPResponseCodeToEnum(GetReponseCode()) == Utils::IotDCPResponseCode::I_OK;
}
