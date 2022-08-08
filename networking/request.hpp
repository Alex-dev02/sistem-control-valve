#pragma once

#include <string>
#include <unordered_map>

#include "utils.hpp"

class Request{
public:
    Request(std::string raw_request);

    std::string GetPath() const;
    std::string GetPathVar(std::string var_name) const;
    std::string GetRawRequest() const;
    Utils::Protocol GetProtocol() const;
private:
    std::string m_raw_request;
    std::unordered_map<std::string, std::string> m_path_vars;
    Utils::Protocol m_protocol;

    void MapVarsFromPath();
};
