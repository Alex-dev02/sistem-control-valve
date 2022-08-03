#pragma once

#include <string>
#include <unordered_map>

#include "Utils.hpp"

class Request{
public:
    Request(std::string raw_request);

    std::string GetPath();
    std::string GetPathVar(std::string var_name);
    std::string GetRawRequest();
    Utils::Protocol GetProtocol();
private:
    std::string m_raw_request;
    std::unordered_map<std::string, std::string> m_path_vars;
    Utils::Protocol m_protocol;

    void MapVarsFromPath();
};
