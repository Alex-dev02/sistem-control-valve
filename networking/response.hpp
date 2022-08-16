#pragma once

#include <string>

#include "utils.hpp"


class Response{
public:
    Response(std::string raw_response);

    std::string GetRawResponse() const;
    Utils::Protocol GetProtocol() const;
    int GetReponseCode() const;

    bool Successful() const;
private:
    std::string m_raw_response;
    Utils::Protocol m_protocol;
};
