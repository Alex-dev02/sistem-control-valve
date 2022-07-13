#pragma once

#include <unordered_map>

class Payload{
    std::unordered_map<std::string, std::string> path_vars;
    std::string raw_http_req;
    void add_path_vars();
public:
    Payload(std::string http_req);
    std::string get_raw_http_req();
    std::string get_path_var(std::string var_name);
};