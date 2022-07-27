#pragma once

#include <string>

#include "Utils.hpp"


class Response{
public:
    Response(std::string raw_response, Utils::Protocol protocol);

    std::string GetRawResponse();
    Utils::Protocol GetProtocol();
    Utils::ResponseCode GetReponseCode();

    bool Successful();
private:
    std::string m_raw_response;
    Utils::Protocol m_protocol;
};
