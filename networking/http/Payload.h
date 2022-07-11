#pragma once

#include <unordered_map>

class Payload{
    std::unordered_map<std::string, std::string> path_vars;
    void add_path_vars(std::string http_response);
public:
    Payload(std::string http_response);
    std::string get_path_var(std::string var_name);
};