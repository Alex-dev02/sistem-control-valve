#pragma once

#include <string>

#include "Utils.hpp"


class Response{
public:
    Response(std::string raw_response);

    std::string GetRawResponse();
    Utils::Protocol GetProtocol();
    int GetReponseCode();

    bool Successful();
private:
    std::string m_raw_response;
    Utils::Protocol m_protocol;
};
