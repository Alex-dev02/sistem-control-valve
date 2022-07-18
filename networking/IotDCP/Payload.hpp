#pragma once

#include <unordered_map>

class Payload {
public:
    Payload(std::string http_req);
    std::string GetRawRequest();
    std::string GetPathVar(std::string var_name);
private:
    std::unordered_map<std::string, std::string> m_path_vars;
    std::string m_raw_http_req;
    void AddPathVars();
};