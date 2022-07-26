#pragma once

#include <string>
#include <unordered_map>

class Request{
public:
    Request(std::string raw_request);

    std::string GetPath();
    std::string GetPathVar(std::string var_name);
    std::string GetRawRequest();
private:
    std::string m_raw_request;
    std::unordered_map<std::string, std::string> m_path_vars;

    void MapVarsFromPath();
};
